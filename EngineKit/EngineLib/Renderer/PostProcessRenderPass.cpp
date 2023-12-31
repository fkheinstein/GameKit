#include <spch.h>




#include "Graphics/VertexArray.h"
#include "Graphics/Shader.h"
#include "Graphics/Framebuffer.h"
#include "Renderer/Renderer.h"


#include "PostProcessRenderPass.h"


namespace fts
{
    struct PostProcessData {
        Device* device;
        ShaderHandle hdr_shader;
        ShaderHandle bloom_shader;

        Ref<Framebuffer> post_target;
        Ref<Texture> post_buffer;

        Ref<Texture> upsample_buffer;
        Ref<Texture> downsample_buffer;
    };

    static PostProcessData s_data;
    static PostProcessSettings s_settings;

    void PostProcessRenderPass::Init(PostProcessSettings settings, Device* device,
        ShaderCache& shaders)
    {
        s_settings = std::move(settings);
        s_data.device = device;

        s_data.hdr_shader = shaders.Load("shader/hdr", "assets/shaders/quad.vert.glsl", "assets/shaders/hdr.frag.glsl");
        s_data.bloom_shader = shaders.Load("shader/bloom", "assets/shaders/bloom.comp.glsl");

        s_data.post_target = Framebuffer::Create();

        InitBuffers();
    }


    void PostProcessRenderPass::SetRenderSize(int32_t width, int32_t height)
    {
        s_settings.width = width;
        s_settings.height = height;
        InitBuffers();
    }

    void PostProcessRenderPass::InitBuffers()
    {
        s_data.post_buffer = Texture::Create(
            s_settings.width, s_settings.height, 1, MultiSampleLevel::None,
            TextureType::Normal2D, DataFormat::RGBA16F,
            { TextureWrap::Edge, TextureMinFilter::Nearest,
             TextureMagFilter::Nearest, MipmapMode::Linear });
        s_data.post_target->Attach(*s_data.post_buffer, 0, 0);

        s_data.downsample_buffer = Texture::Create(
            s_settings.width, s_settings.height, 1, MultiSampleLevel::None,
            TextureType::Normal2D, DataFormat::RGBA16F,
            { TextureWrap::Edge, TextureMinFilter::Linear, TextureMagFilter::Linear,
             MipmapMode::Linear },
            7);
        s_data.upsample_buffer = Texture::Create(
            s_settings.width, s_settings.height, 1, MultiSampleLevel::None,
            TextureType::Normal2D, DataFormat::RGBA16F,
            { TextureWrap::Edge, TextureMinFilter::Linear, TextureMagFilter::Linear,
             MipmapMode::Linear },
            s_data.downsample_buffer->GetMipmapLevels() - 1);
    }


    void DrawTexture(const fts::Texture& texture, const ImVec2& uv0, const ImVec2& uv1)
    {
        ImVec2 wsize = ImGui::GetContentRegionAvail();
        const float width = texture.GetWidth() * std::abs(uv1.x - uv0.x);
        const float height = texture.GetHeight() * std::abs(uv1.y - uv0.y);
        const float ASPECT = height / width;
        wsize.y = wsize.x * ASPECT;

        ImGui::Image((void*)(intptr_t)texture.Handle(), wsize, uv0, uv1);
    }


    void PostProcessRenderPass::ImGui()
    {
        ImGui::SliderFloat("Exposure", &s_settings.exposure, 0, 10);
        ImGui::SliderFloat("Gamma Correction", &s_settings.gamma_correction, 0.1, 3);
        ImGui::Checkbox("Bloom", &s_settings.is_bloom);
        ImGui::SliderFloat("Bloom Threshold", &s_settings.bloom_threshold, 0, 1.0);
        ImGui::SliderFloat("Bloom Soft Threshold", &s_settings.bloom_soft_threshold,  0.01, 1.0f);

        static int base_level = 0;
        static int buffer_index = 0;
        ImGui::SliderInt("Buffer index", &buffer_index, 0, 1);
        Texture* buffer = buffer_index == 0 ? s_data.downsample_buffer.get() : s_data.upsample_buffer.get();

        ImGui::SliderInt("Base level", &base_level, 0, buffer->GetMipmapLevels() - 1);
        buffer->SetBaseLevel(base_level);

        DrawTexture(*buffer, ImVec2(0, 1), ImVec2(1, 0));
    }

    void PostProcessRenderPass::Render()
    {
        Framebuffer* fb = Renderer::GetCurrentRenderPass().framebuffer;
        s_data.device->ReadBuffer(fb, 0);
        s_data.device->DrawBuffer(s_data.post_target.get(), 0);
        s_data.device->BlitFramebuffer(
            fb, 0, 0, s_settings.width, s_settings.height, s_data.post_target.get(),
            0, 0, s_settings.width, s_settings.height,
            BufferBitMask::ColorBufferBit, BlitFilter::Nearest);

        if (s_settings.is_bloom) {
            RenderBloom();
        }
        RenderPost();
    }

    void PostProcessRenderPass::RenderPost()
    {
        int index = 0;
        RenderSubpassInfo info{ &index, 1 };
        Renderer::BeginRenderSubpass(info);

        s_data.hdr_shader->GetParam("u_bloom")->SetAsBool(s_settings.is_bloom);
        s_data.hdr_shader->GetParam("u_upsample_buffer")->SetAsTexture(s_data.upsample_buffer.get());
        s_data.hdr_shader->GetParam("u_lighting")->SetAsTexture(s_data.post_buffer.get());
        s_data.hdr_shader->GetParam("u_exposure")->SetAsFloat(s_settings.exposure);
        s_data.hdr_shader->GetParam("u_gamma")->SetAsFloat(s_settings.gamma_correction);

        Renderer::DrawNDCQuad(*s_data.hdr_shader);

        Renderer::EndRenderSubpass();
    }

    void PostProcessRenderPass::Downsample(Texture& src, Texture& dst)
    {
        s_data.bloom_shader->GetParam("u_downsample")->SetAsBool(true);
        s_data.bloom_shader->GetParam("u_threshold")->SetAsFloat(s_settings.bloom_threshold);
        const float knee =  s_settings.bloom_threshold * s_settings.bloom_soft_threshold;

        Vector3f filter;
        filter.x = s_settings.bloom_threshold - knee;
        filter.y = 2.f * knee;
        filter.z = 0.25f / (knee + 1e-4);
        s_data.bloom_shader->GetParam("u_curve")->SetAsVec3(&filter[0]);

        for (int base_level = 0; base_level < dst.GetMipmapLevels(); ++base_level) {
            if (base_level == 0) {
                s_data.bloom_shader->GetParam("u_input")->SetAsBool(true);
                s_data.bloom_shader->GetParam("u_out_image")->SetAsImage(&dst, 0, false, 0, Access::WriteOnly);
                s_data.bloom_shader->GetParam("u_in_texture")->SetAsTexture(&src);
            }
            else {
                s_data.bloom_shader->GetParam("u_input")->SetAsBool(false);
                s_data.bloom_shader->GetParam("u_out_image")->SetAsImage(&dst, base_level, false, 0, Access::WriteOnly);
                s_data.bloom_shader->GetParam("u_level")->SetAsInt(base_level - 1);
                s_data.bloom_shader->GetParam("u_in_texture")->SetAsTexture(&dst);
            }
            Renderer::ComputeImage(*s_data.bloom_shader, s_settings.width,s_settings.height, 1);
        }
    }

    void PostProcessRenderPass::Upsample(Texture& src, Texture& dst)
    {
        const int max_level = dst.GetMipmapLevels() - 1;
        s_data.bloom_shader->GetParam("u_downsample")->SetAsBool(false);

        for (int base_level = max_level; base_level >= 0; --base_level) {
            s_data.bloom_shader->GetParam("u_level")->SetAsInt(base_level + 1);

            if (base_level == max_level) {
                s_data.bloom_shader->GetParam("u_input")->SetAsBool(true);
                s_data.bloom_shader->GetParam("u_out_image")->SetAsImage(&dst, base_level, false, 0, Access::WriteOnly);
                s_data.bloom_shader->GetParam("u_in_texture")->SetAsTexture(&src);
            }
            else 
            {
                s_data.bloom_shader->GetParam("u_input")->SetAsBool(false);
                s_data.bloom_shader->GetParam("u_out_image")->SetAsImage(&dst, base_level, false, 0, Access::WriteOnly);
                s_data.bloom_shader->GetParam("u_down_texture")->SetAsTexture(&src);
                s_data.bloom_shader->GetParam("u_in_texture")->SetAsTexture(&dst);
            }
            Renderer::ComputeImage(*s_data.bloom_shader, s_settings.width,  s_settings.height, 1);
        }
    }

    void PostProcessRenderPass::RenderBloom()
    {
        // make sure base level is readable
        s_data.downsample_buffer->SetBaseLevel(0);
        s_data.upsample_buffer->SetBaseLevel(0);
        Downsample(*s_data.post_buffer, *s_data.downsample_buffer);
        Upsample(*s_data.downsample_buffer, *s_data.upsample_buffer);
    }

} // namespace fts
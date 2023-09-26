#ifndef __POSTPROCESSRENDERPASS_H__
#define __POSTPROCESSRENDERPASS_H__

#include "Resource/Resource.h"
#include "Graphics/Device.h"

namespace fts
{
    struct PostProcessSettings {
        int width;
        int height;

        float bloom_threshold{ 1.0 };
        float bloom_soft_threshold{ 0.8 };

        bool is_bloom{ true };
        float exposure{ 1.0 };
        float gamma_correction{ 1.5 };
    };

    class PostProcessRenderPass {
    public:
        static void Init(PostProcessSettings settings, Device* device,  ShaderCache& shaders);

        static void SetRenderSize(int32_t width, int32_t height);

        static void ImGui();

        static void Render();

    private:
        static void RenderPost();

        static void RenderBloom();
        static void Downsample(Texture& src, Texture& dst);
        static void Upsample(Texture& src, Texture& dst);

        static void InitBuffers();
    };
} // namespace fts

#endif // __POSTPROCESSRENDERPASS_H__
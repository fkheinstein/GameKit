#include <spch.h>

#include "GraphicsLayer.h"



#include "Graphics/Device.h"
#include "Graphics/Texture.h"
#include "Graphics/Framebuffer.h"
#include "Graphics/Shader.h"

#include "Graphics/Renderbuffer.h"

#include <Renderer/Renderer.h>
#include <Renderer/Renderer2D.h>
#include <Renderer/Renderer3D.h>

#include <Renderer/PostProcessRenderPass.h>
#include <Renderer/SpriteRenderPass.h>
#include <Renderer/SkyboxRenderPass.h>
#include <Renderer/DeferredRenderPass.h>

#include "ECS/Component.h"
#include "ECS/SceneManager.h"



#include "Camera/Camera.h"
#include "Camera/PerspectiveCamera.h"
#include "Camera/CameraController.h"
#include "Camera/PerspectiveCameraController.h"


namespace fts {

    GraphicsLayer::GraphicsLayer(ResourceManager *resources, SceneManager *scenes,Device* device, int32_t width, int32_t height, MultiSampleLevel msaa)
        : Layer("GraphicsLayer")
        , m_resources(resources)
        , m_scenes(scenes)
        , m_device(device)
        , m_width(width)
        , m_height(height)
        , m_msaa(msaa)
        , m_color_output(nullptr)
        , m_color_output_attachment(0)
        , m_fps(20)
    {
        m_main_target = Framebuffer::Create();

        InitBuffers();


        Renderer::Init(m_device);
        Renderer2D::Init(m_resources->shaders);
        Renderer3D::Init();


        SkyboxRenderPass::Init(m_resources->shaders, m_resources->textures.Get("skybox/default").Get());
        PostProcessRenderPass::Init(PostProcessSettings{ m_width, m_height }, m_device, m_resources->shaders);
        DeferredRenderPass::Init(DeferredRenderSettings{ m_width, m_height, m_msaa }, m_device, m_resources->shaders , m_resources->models);


        PostProcessRenderPass::Init(PostProcessSettings{ m_width, m_height }, m_device, m_resources->shaders);
        SpriteRenderPass::Init(m_resources->textures);

        m_light_icon = m_resources->textures.Get("icon/light");


        mWindowResize = fts::evt::EventManager::eventDispatcher.appendListener(
            fts::evt::EventType::WindowResize,

            eventpp::argumentAdapter<void(const fts::evt::WindowResizeEvent&)>(
                [this](const fts::evt::WindowResizeEvent& evt) {

                    FTS_CORE_TRACE(evt.ToString());
                    this->SetRenderSize(evt.GetWidth(), evt.GetHeight());
                }
            )
        );

    }


    void GraphicsLayer::InitBuffers()
    {
        m_color_buffer = Texture::Create(m_width, m_height, 1, m_msaa,  TextureType::Normal2D, DataFormat::RGBA8);
        m_depth_buffer = Renderbuffer::Create(m_width, m_height, m_msaa, DataFormat::Depth24);

        m_main_target->Attach(*m_color_buffer, 0, 0);
        m_main_target->Attach(*m_depth_buffer, 0);     
    }


    void GraphicsLayer::OutputColorBuffer(Framebuffer* framebuffer, int attachment)
    {
        m_color_output = framebuffer;
        m_color_output_attachment = attachment;
    }


    void GraphicsLayer::OnRender() {

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 1.0f, 0.0f, 0.0f);


        Scene* scene = m_scenes->GetCurrentScene();
        TransformComponent transformComp;
        CameraComponent cameraComp;

        // update camera transform
        auto view = scene->view<CameraComponent, TransformComponent>();
        view.each([&](CameraComponent& camComp, TransformComponent& trans) {
            //camComp.camera.SetWorldTransform(trans.GetWorldTransform().GetMatrix());
            cameraComp = camComp;
            transformComp = trans;


            });

        auto& camera = cameraComp.cameraController->GetCamera();


        /*if (cameraComp.camera == nullptr) 
        {
            FTS_ASSERT_MSG(false, "Camera cannot be null");
        }*/


        //Renderer::BeginRenderPass({ m_main_target.get(), m_width, m_height });
        //Renderer::SetCamera(*m_camera);

        uint32_t id = static_cast<uint32_t>(entt::null);
        m_main_target->ClearAttachment(1, &id);


        // main render pipeline
        m_deferred_time = 0;
        m_post_rendering_time = 0;
        Clock clock;


    }

    void GraphicsLayer::OnTick(float dt) {

        // main render pipeline
        m_deferred_time = 0;
        m_post_rendering_time = 0;
        Clock clock;

        Scene* scene = m_scenes->GetCurrentScene();
        auto view = scene->view<CameraComponent>();
        view.each([&](CameraComponent& camComp) {
            
            camComp.cameraController->OnUpdate(dt);
            });



        if (m_debug) {
            const int index[] = { 0, 1 };

        }



        //// Blit output
        //m_device->ReadBuffer(m_main_target.get(), 0);
        //if (m_color_output || (m_color_output == nullptr && m_color_output_attachment == 0))
        //{
        //    m_device->DrawBuffer(m_color_output, m_color_output_attachment);
        //    m_device->BlitFramebuffer(m_main_target.get(), 0, 0, m_width, m_height, m_color_output, 0, 0, 
        //        m_width, m_height, BufferBitMask::ColorBufferBit, BlitFilter::Nearest);
        //}
    }



    uint32_t GraphicsLayer::ReadEntityId(int x, int y) const
    {
        uint32_t id = -1;
        const Texture* entity_buffer = DeferredRenderPass::GetEntityBuffer();
        if (x >= 0 && y >= 0 && x < entity_buffer->GetWidth() &&
            y < entity_buffer->GetHeight()) {
            entity_buffer->ReadPixels(0, x, y, 0, 1, 1, 1, sizeof(id), &id);
        }
        return id;
    }

    void GraphicsLayer::OnImGui()
    {
        if (m_debug) {
            const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Framed |
                ImGuiTreeNodeFlags_SpanAvailWidth |
                ImGuiTreeNodeFlags_AllowItemOverlap |
                ImGuiTreeNodeFlags_FramePadding;
            ImGui::Begin("Graphics Debug");
            {
                if (ImGui::TreeNodeEx("Profiles",
                    flags | ImGuiTreeNodeFlags_DefaultOpen)) {
                    ImGui::TextUnformatted("Renderer2D Debug Info:");
                    ImGui::TextWrapped("%s", Renderer2D::GetDebugInfo().c_str());
                    ImGui::TextUnformatted("Renderer3D Debug Info:");
                    ImGui::TextWrapped("%s", Renderer3D::GetDebugInfo().c_str());
                    ImGui::Text("FPS:%.2f(%.2f ms)", m_fps.GetFPS(),
                        m_fps.GetFrameTime());
                    ImGui::TreePop();
                }
                if (ImGui::TreeNodeEx("Deferred Render Pass", flags)) {
                    ImGui::TextUnformatted("Deferred Rendering Time:");
                    ImGui::TextWrapped("%.2f ms", m_deferred_time);
                    DeferredRenderPass::ImGui();
                    ImGui::TreePop();
                }
                if (ImGui::TreeNodeEx("Post Process Render Pass", flags)) {
                    ImGui::TextUnformatted("Post Process Rendering Time:");
                    ImGui::TextWrapped("%.2f ms", m_post_rendering_time);
                    PostProcessRenderPass::ImGui();
                    ImGui::TreePop();
                }
            }
            ImGui::End();
            // Reset debug info
            Renderer2D::Reset();
            Renderer3D::Reset();
        }
    }



    void GraphicsLayer::SetRenderSize(int32_t width, int32_t height)
    {
        m_width = width;
        m_height = height;
        InitBuffers();


        DeferredRenderPass::SetRenderSize(width, height);
        PostProcessRenderPass::SetRenderSize(width, height);
    }

    void GraphicsLayer::SetCamera(Camera* camera) { m_camera = camera; }


}
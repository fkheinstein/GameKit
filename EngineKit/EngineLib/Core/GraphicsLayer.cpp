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


#include "ECS/Component.h"
#include "ECS/SceneManager.h"




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

        m_light_icon = m_resources->textures.Get("icon/light");


        fts::evt::EventManager::eventDispatcher.appendListener(evt::EventType::WindowResize, [this](const evt::Event& event) {
            //this->SetRenderSize(event);
            });

    }


    void GraphicsLayer::InitBuffers()
    {
        m_color_buffer = Texture::Create(m_width, m_height, 1, m_msaa,  TextureType::Normal2D, DataFormat::RGBA8);
        m_depth_buffer = Renderbuffer::Create(m_width, m_height, m_msaa, DataFormat::Depth24);

        m_main_target->Attach(*m_color_buffer, 0, 0);
        m_main_target->Attach(*m_depth_buffer, 0);


        mWindowResize = fts::evt::EventManager::eventDispatcher.appendListener(
            fts::evt::EventType::WindowResize,

            eventpp::argumentAdapter<void(const fts::evt::WindowResizeEvent&)>(
                [this](const fts::evt::WindowResizeEvent& evt) {


                    evt.ToString();

                    this->SetRenderSize(evt.GetWidth(), evt.GetHeight());
                }
            )
        );
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


    void GraphicsLayer::OnImGui() {

    }



    void GraphicsLayer::SetRenderSize(int32_t width, int32_t height)
    {
        m_width = width;
        m_height = height;
        InitBuffers();
    }

    void GraphicsLayer::SetCamera(Camera* camera) { m_camera = camera; }

    void GraphicsLayer::OutputColorBuffer(Framebuffer* framebuffer, int attachment)
    {
        m_color_output = framebuffer;
        m_color_output_attachment = attachment;
    }
}
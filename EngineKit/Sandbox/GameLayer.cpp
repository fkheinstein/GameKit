#include <spch.h>


#include "GameLayer.h"
#include <Application/IApplication.h>


#include <ECS/Entity.h>

#include <Graphics/Framebuffer.h>
#include <Renderer/Renderer2D.h>

namespace app01
{

    using namespace fts;

    GameLayer::GameLayer(fts::InputDevice* input, SceneManager* scenes, ResourceManager* resources, fts::GraphicsLayer* graphics_layer, int width, int height)
        : fts::Layer("GameLayer")
        , m_graphics_layer(graphics_layer)
        , m_resources(resources)
        , m_scenes(scenes)


        , m_viewport_pos(0, 0)
        , m_viewport_size(width, height)

        , m_quitting(false)
    {



        static const struct
        {
            float x, y;
            float r, g, b;
        } vertices[] =
        {
            { -0.6f, -0.4f, 1.f, 0.f, 0.f },
            {  0.6f, -0.4f, 0.f, 1.f, 0.f },
            {   0.f,  0.6f, 0.f, 0.f, 1.f },
            { -0.3f,  0.8f, 1.f, 0.f, 1.f },
        };
        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3,
        };


        m_graphics_layer->SetRenderSize(m_viewport_size.x, m_viewport_size.y);        
        //m_graphics_layer->SetCamera(&m_editor_camera);

        //m_viewport_target = fts::Framebuffer::Create();
        //m_graphics_layer->OutputColorBuffer(m_viewport_target.get(), 0);

    }


    void GameLayer::OnPush() {

        m_scenes->EmplaceScene("Empty Scene");

        Scene* scene = m_scenes->GetCurrentScene();

        /*   m_scenes->GetCurrentScene()->CreateEntity("Camera")
               .AddComponent<CameraComponent>()
               .AddComponent<NativeScriptComponent>()
               .GetComponent<Hazel::NativeScriptComponent>()
               .Bind<CameraController>(viewPortWidth, viewPortHeight, (1.0f / m_FixedTimestep) - 1.0f)
               ;*/


        auto entityCamera = scene->CreateEntity("Camera");

        //if (!entityCamera.HasComponent<CameraComponent>())
        //    entityCamera.AddComponent<CameraComponent>(CameraType::Perspective,  glm::radians(45.f), 400,  400, 0.1f, 1000.f);


    }

    void GameLayer::OnPop() {


    }


    void GameLayer::OnTick(float dt) {}
    void GameLayer::OnRender() {}
    void GameLayer::OnImGui() {
    
        ImGui::Begin("GameLayer Example");
        ImGui::Text("Version 1.0v");
        ImGui::End();

        //ImGui::Separator();
        //auto stats = fts::Renderer:::GetStats();
        //ImGui::Text("Renderer2D Stats:");
        //ImGui::Text("Draw Calls: %d", stats.DrawCalls);
        //ImGui::Text("Quads: %d", stats.QuadCount);
        //ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
        //ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
        //ImGui::Text("Textures: %d", stats.TextureCount);
        //float averageRenderTime = stats.TotalFrameRenderTime / stats.FrameRenderTime.size(); // nb: wont be accurate until we have gathered at least stats.FrameRenderTime().size() results
        //float averageFPS = 1.0f / averageRenderTime;
        //ImGui::Text("Average frame render time: %8.5f (%5.0f fps)", averageRenderTime, averageFPS);
    }


    void GameLayer::Quit() {
        m_quitting = true;

        fts::Application::GetApp().Shutdown();
    }

    void GameLayer::On(const fts::AppQuitEvent&) { Quit(); }

    void GameLayer::On(const fts::KeyEvent& e)
    {

        if (!e.state) return;

        switch (e.keycode) {
        default:
            break;

        case fts::Keycode::Z: {


        } break;
        case fts::Keycode::Escape: {
            Quit();
        } break;
        }
    }


    void GameLayer::On(const fts::MouseMotionEvent& e)
    {

    }

    void GameLayer::On(const fts::MouseButtonEvent& e)
    {

    }


} // namespace app01

#include <spch.h>


#include "GameLayer.h"
#include <Application/IApplication.h>


#include <Graphics/Framebuffer.h>

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

        m_graphics_layer->SetRenderSize(m_viewport_size.x, m_viewport_size.y);        
        //m_graphics_layer->SetCamera(&m_editor_camera);

        //m_viewport_target = fts::Framebuffer::Create();
        //m_graphics_layer->OutputColorBuffer(m_viewport_target.get(), 0);

        m_scenes->EmplaceScene("Empty Scene");
    }

    void GameLayer::OnTick(float dt) {}
    void GameLayer::OnRender() {}
    void GameLayer::OnImGui() {
    
        ImGui::Begin("GameLayer Example");
        ImGui::Text("Version 1.0v");
        ImGui::End();
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

#include <spch.h>


#include "GameLayer.h"
#include <Application/IApplication.h>

namespace app01
{

    GameLayer::GameLayer(fts::InputDevice* input, /*SceneManager* scenes, ResourceManager* resources,*/ fts::GraphicsLayer* graphics_layer
        , int width, int height)
        : fts::Layer("EditorLayer")
        , m_graphics_layer(graphics_layer)
        , m_quitting(false)
    {

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

#include <sCore.h>

#include "SceneBuilderLayer.h"

#include <Application/IApplication.h>


#include <ECS/Entity.h>

#include <Graphics/Framebuffer.h>
#include <Renderer/Renderer2D.h>



namespace app01
{

    SceneBuilder::SceneBuilder() : fts::Layer("SceneBuilder")
        //, m_graphics_layer(graphics_layer)
    {

    }


    SceneBuilder::~SceneBuilder()
    {
    }


    void SceneBuilder::OnPush() {
    

    }

    void SceneBuilder::OnPop() {
    

    }


    void SceneBuilder::CreateObject()
    {
        auto* scene = fts::Application::GetApp().GetSceneManager().GetCurrentScene();
        {
        }
    }

    void SceneBuilder::CreateEnemyShip()
    {
    }

    void SceneBuilder::CreateDirLight()
    {
    }

    void SceneBuilder::CreateUIObject()
    {
    }

} // namespace app01
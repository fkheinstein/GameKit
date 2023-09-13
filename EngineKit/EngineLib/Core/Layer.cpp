#include <spch.h>


#include "Layer.h"

#include <Application/IApplication.h>
#include <ECS/SceneManager.h>
#include <Resource/ResourceManager.h>

namespace fts
{

        Layer::Layer(const std::string &name) : m_name(name)
        , IsEnabled(true)
        , mApp(Application::GetApp())
        , mSceneManager(Application::GetApp().GetSceneManager())
        , mResource(Application::GetApp().GetResourceManager())
        {
            FTS_CORE_TRACE("Initializing layer: {}", name);
        }

        Layer::~Layer() { FTS_CORE_TRACE("Deleting layer: {}", m_name); }

}
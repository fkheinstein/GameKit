#include <sCore.h>

#include "SandboxApp.h"





IMPLEMENT_APP(app01::SandboxApp);


namespace app01
{


    SandboxApp::SandboxApp(/* args */) : Application("Basic Application", fts::Device::API::OpenGL) 
    {
    }


    void SandboxApp::OnInit()
    {
        Application::OnInit();
        auto& settings = GetSettings();
        int viewport_width = settings.GetInteger("editor", "viewport width", 800);
        int viewport_height = settings.GetInteger("editor", "viewport height", 600);

        CreateImGuiLayer();
        
        //m_graphics_layer->SetDebug(true);
        //PushLayer(CreateLayer<EditorLayer>(&m_input, &m_scenes, &m_resources,  m_graphics_layer, viewport_width, viewport_height));
    }

    void SandboxApp::OnDestroy() 
    {
        Application::OnDestroy(); 
    }

} // namespace fts
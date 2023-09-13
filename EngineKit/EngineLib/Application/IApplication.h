#ifndef __IAPPLICATION_H__
#define __IAPPLICATION_H__


#include "Core/Window.h"

#include "Core/ImGuiLayer.h"


#include "Graphics/Device.h"
#include "Core/InputDevice.h"
#include "ECS/SceneManager.h"
#include "Resource/ResourceManager.h"
#include "Utils/Init.h"

#include <filesystem>

int main(int argc, char** argv);



#define IMPLEMENT_APP(X)                          \
    int main(int, char **)                        \
    {                                             \
        fts::Application::s_instance = new X;      \
        fts::Application::s_instance->OnInit();    \
        fts::Application::s_instance->Run();       \
        fts::Application::s_instance->OnDestroy(); \
        delete fts::Application::s_instance;       \
        return 0;                                  \
    }


namespace fts
{
    class GraphicsLayer;
    class Application    
    {
    public:
        template <typename T = Application>
        static T& GetApp()
        {
            return *dynamic_cast<T*>(s_instance);
        }

        void Shutdown();


        Ini& GetSettings() { return m_settings; };
        SceneManager& GetSceneManager() {return m_scenes;}
        InputDevice& GetInput() {return m_input;}
        ResourceManager& GetResourceManager() {return m_resources;}


    protected:
        virtual void OnInit();
        virtual void OnDestroy();

        template <typename T>
        T* GetLayer(const std::string& name)
        {
            auto iter = std::find_if(
                m_layers.begin(), m_layers.end(),
                [&name](const auto& lhs) { return lhs->GetName() == name; });
            if (iter != m_layers.end()) {
                return static_cast<T*>(*iter);
            }
            return nullptr;
        }


        template <typename T, typename... ARGS>
        T* CreateLayer(ARGS &&...args)
        {
            T* layer = new T(std::forward<ARGS>(args)...);
            return layer;
        }

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        void PopLayer(Layer* layer);
        void DestroyLayer(Layer* layer);

        void CreateImGuiLayer();

        Application(const std::string& title, Device::API api);
        virtual ~Application();

        Application(const Application& application) = delete;
        Application& operator=(const Application& application) = delete;

        Scope<Window> m_window;
        Scope<Device> m_device;

        ResourceManager m_resources;
        SceneManager m_scenes;
        InputDevice m_input;
        GraphicsLayer* m_graphics_layer;

    private:
        ImGuiLayer* m_imgui_layer;

        friend int ::main(int argc, char** argv);

        void LoadSettingsFile();

        void Run();

        void Tick(float dt);

        void Render();

        EventStack<Layer*> m_layers;

        Ini m_settings;

        static Application* s_instance;

        std::filesystem::path GetAppDirectory();
    };


} // namespace fts

#endif // __IAPPLICATION_H__
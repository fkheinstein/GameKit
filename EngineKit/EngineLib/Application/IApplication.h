#ifndef __IAPPLICATION_H__
#define __IAPPLICATION_H__


#include "Core/Window.h"

#include "Core/ImGuiLayer.h"
//#include "Core/GraphicsLayer.hpp"


#include "Graphics/Device.h"


#include "Utils/Init.h"


namespace fts
{
    class  Application {
    public:
        template <typename T = Application>
        static T& GetApp()
        {
            return *dynamic_cast<T*>(s_instance);
        }

        void Shutdown();

        Ini& GetSettings() { return m_settings; };

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

        /*GraphicsLayer* m_graphics_layer;
        ResourceManager m_resources;
        SceneManager m_scenes;
        InputDevice m_input;*/

    private:
        ImGuiLayer* m_imgui_layer;

        //friend int ::main(int argc, char** argv);

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
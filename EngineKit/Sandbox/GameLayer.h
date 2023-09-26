#ifndef A293CBBB_C9D1_476D_9F22_E54677CA3A34
#define A293CBBB_C9D1_476D_9F22_E54677CA3A34


#include "Core/GraphicsLayer.h"
#include "Core/Layer.h"
#include "Core/InputDevice.h"

#include <Camera/Camera.h>
#include <Camera/CameraController.h>


namespace app01
{

    class GameLayer : public fts::Layer {
    public:
        GameLayer(fts::InputDevice* input, fts::SceneManager* scenes, fts::ResourceManager* resources, fts::GraphicsLayer* graphics_layer, int width, int height);
        ~GameLayer()= default;

        void OnTick(float dt) override;
        void OnRender() override;
        void OnImGui() override;

        void OnPush() override;
        void OnPop() override;


    private:
        void Quit();
        bool m_quitting;


    private:
        void On(const fts::KeyEvent& e) override;
        void On(const fts::AppQuitEvent& e) override;
        void On(const fts::MouseMotionEvent& e) override;
        void On(const fts::MouseButtonEvent& e) override;


        fts::GraphicsLayer* m_graphics_layer;
        fts::SceneManager* m_scenes;
        fts::ResourceManager* m_resources;

        glm::ivec2 m_viewport_pos;
        glm::ivec2 m_viewport_size;



        Ref<fts::Framebuffer> m_viewport_target;
        Ref<fts::Texture> m_scene_buffer;


        Ref<fts::CameraController> mCameraController;


    };
} // namespace app01


#endif /* A293CBBB_C9D1_476D_9F22_E54677CA3A34 */

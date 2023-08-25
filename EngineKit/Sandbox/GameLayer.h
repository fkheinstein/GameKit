#ifndef A293CBBB_C9D1_476D_9F22_E54677CA3A34
#define A293CBBB_C9D1_476D_9F22_E54677CA3A34


#include "Core/GraphicsLayer.h"
#include "Core/Layer.h"
#include "Core/InputDevice.h"

namespace app01
{

    class GameLayer : public fts::Layer {
    public:
        GameLayer(fts::InputDevice* input, /*SceneManager* scenes, ResourceManager* resources,*/ fts::GraphicsLayer* graphics_layer, int width, int height);
        ~GameLayer()= default;

        void OnTick(float dt) override;
        void OnRender() override;
        void OnImGui() override;


    private:
        void Quit();
        bool m_quitting;
    private:
        void On(const fts::KeyEvent& e) override;
        void On(const fts::AppQuitEvent& e) override;
        void On(const fts::MouseMotionEvent& e) override;
        void On(const fts::MouseButtonEvent& e) override;
        
        fts::GraphicsLayer* m_graphics_layer;
    };
} // namespace app01


#endif /* A293CBBB_C9D1_476D_9F22_E54677CA3A34 */

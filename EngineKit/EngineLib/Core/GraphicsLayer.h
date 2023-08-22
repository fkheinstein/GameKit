#ifndef D24630B8_CC40_49FB_8A91_FBA17CF46F09
#define D24630B8_CC40_49FB_8A91_FBA17CF46F09

#include "Core/Layer.h"
#include "Graphics/Device.h"

namespace fts
{
    class GraphicsLayer : public Layer
    {
    public:
        GraphicsLayer(ResourceManager *resources, SceneManager *scenes,  Device *device, int32_t width, int32_t height, MultiSampleLevel msaa);
        void OnImGui() override;
        void OnRender() override;
        void OnTick(float dt) override;
    };
} // namespace fts

#endif /* D24630B8_CC40_49FB_8A91_FBA17CF46F09 */

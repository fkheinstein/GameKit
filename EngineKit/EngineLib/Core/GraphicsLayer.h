#ifndef D24630B8_CC40_49FB_8A91_FBA17CF46F09
#define D24630B8_CC40_49FB_8A91_FBA17CF46F09

#include "Core/Layer.h"
#include "Graphics/Graphics.h"
#include "Utils/Timing.h"

#include <Resource/Resource.h>
#include <Resource/ResourceManager.h>

namespace fts
{
    class Renderbuffer;
    class Framebuffer;
    class Device;
    class Texture;
    class Camera;
    class SceneManager;
    class ResourceManager;
    class GraphicsLayer : public Layer
    {
    public:
        GraphicsLayer(ResourceManager *resources, SceneManager* scenes, Device *device, int32_t width, int32_t height, MultiSampleLevel msaa);
        void OnImGui() override;
        void OnRender() override;
        void OnTick(float dt) override;


        void SetRenderSize(int32_t width, int32_t height);
        void SetCamera(Camera* camera);
        void SetDebug(bool debug) { m_debug = debug; }


        Framebuffer* GetFramebuffer() { return m_main_target.get(); }
        void OutputColorBuffer(Framebuffer* framebuffer, int attachment);
        uint32_t ReadEntityId(int x, int y) const;

    private:
        void InitBuffers();
    
        ResourceManager* m_resources;
        SceneManager* m_scenes;
        Device* m_device;
        int32_t m_width;
        int32_t m_height;
        MultiSampleLevel m_msaa;
        bool m_debug;

        Ref<Framebuffer> m_main_target;
        Ref<Texture> m_color_buffer;
        Framebuffer* m_color_output;
        int32_t m_color_output_attachment;

        Ref<Renderbuffer> m_depth_buffer;
        TextureHandle m_light_icon;

        Camera* m_camera;
        FPSCounter m_fps;
        float m_deferred_time;
        float m_post_rendering_time;
    };

} // namespace fts

#endif /* D24630B8_CC40_49FB_8A91_FBA17CF46F09 */

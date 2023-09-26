#ifndef __DEFERREDRENDERPASS_H__
#define __DEFERREDRENDERPASS_H__


#include "ECS/Scene.h"
#include "Graphics/Device.h"
#include "Graphics/Framebuffer.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"
#include "Graphics/CascadeShadow.h"
#include "Graphics/PointShadow.h"
#include "Resource/Resource.h"


namespace fts
{
    enum class GeometryBufferType
    {
        Position = 0,
        Normal,
        Albedo,
        Ambient,
        Emissive,
        EntityId,
        GBufferCount
    };

    struct DeferredRenderSettings
    {
        int32_t width;
        int32_t height;
        MultiSampleLevel msaa;
        bool ssao_state{true};
        float ssao_radius{2.0f};
        float ssao_bias{0.5};
        int ssao_power{3};
    };

    DataFormat GetTextureFormat(GeometryBufferType type);

    class DeferredRenderPass
    {
    public:
        static void Init(DeferredRenderSettings settings, Device *device, ShaderCache &shaders, ModelCache &models);

        static void Render(Scene &scene);

        static void ImGui();
        static void DrawTexture(const fts::Texture& texture, const ImVec2& uv0, const ImVec2& uv1);

        static void SetRenderSize(int32_t width, int32_t height);

        static Texture *GetEntityBuffer();

    private:
        static void InitShaders(ShaderCache &cache);
        static void InitSSAOBuffers();
        static void InitSSAOKernel();
        static void InitLightingBuffers();

        static void RenderGBuffer(const Scene &scene);
        static void BlitGeometryBuffers();

        static void RenderSSAO();

        static void RenderShadowMap(const Scene &scene, CascadeShadow &shadow,
                                    const Camera &camera,
                                    const Transform &transform);
        static void RenderPointShadowMap(const Scene &scene, PointShadow &shadow,
                                         const Transform &transform);
        static void RenderDeferred(Scene &scene);
        static void RenderEmissive();
    };

} // namespace fts

#endif // __DEFERREDRENDERPASS_H__
#ifndef __SKYBOXRENDERPASS_H__
#define __SKYBOXRENDERPASS_H__


#include <Resource/Resource.h>

namespace fts
{
    class Texture;
    class  SkyboxRenderPass {
    public:
        static void Init(ShaderCache& shaders, const Texture* skybox);
        static void Render();
    };
} // namespace fts


#endif // __SKYBOXRENDERPASS_H__
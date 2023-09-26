#ifndef __SPRITERENDERPASS_H__
#define __SPRITERENDERPASS_H__

#include <Resource/Resource.h>
#include <ECS/Scene.h>

namespace fts
{
    class SpriteRenderPass {
    public:
        static void Init(TextureCache& textures);
        static void Render(const Scene& scene);
    };
} // namespace fts


#endif // __SPRITERENDERPASS_H__
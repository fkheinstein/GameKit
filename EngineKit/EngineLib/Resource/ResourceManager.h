#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include "Resource/Resource.h"

namespace fts
{
class  ResourceManager {
   public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    ImageCache images;

    TextureCache textures;

    //ModelCache models;

    ShaderCache shaders;
};

} // namespace fts



#endif // __RESOURCEMANAGER_H__
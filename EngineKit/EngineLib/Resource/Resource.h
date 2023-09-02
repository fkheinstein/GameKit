#ifndef __RESOURCE_H__
#define __RESOURCE_H__


#include "Resource/TextureLoader.h"
#include "Resource/ModelLoader.h"
#include "Resource/ImageLoader.h"
#include "Resource/ShaderLoader.h"
#include "Resource/ResourceCache.h"


namespace fts
{


template <typename LoaderType>
struct Loader : LoaderType {
    template <typename... Args>
    auto operator()(Args &&...args)
    {
        return LoaderType::Load(std::forward<Args>(args)...);
    }
};



using ImageHandle = ResourceHandle<ByteImage>;
using ImageCache = ResourceCache<ByteImage, Loader<ImageLoader>>;

using TextureHandle = ResourceHandle<Texture>;
using TextureCache = ResourceCache<Texture, Loader<TextureLoader>>;

using ModelHandle = ResourceHandle<Model>;
using ModelCache = ResourceCache<Model, Loader<ModelLoader>>;

using ShaderCache = ResourceCache<Shader, Loader<ShaderLoader>>;
using ShaderHandle = ResourceHandle<Shader>;


} // namespace fts



#endif // __RESOURCE_H__
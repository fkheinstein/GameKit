#ifndef __TEXTURELOADER_H__
#define __TEXTURELOADER_H__

#include "Graphics/Texture.h"
#include "Core/Base.h"

namespace fts
{
    class TextureLoader
    {
    public:
        Ref<Texture> Load(const std::string &path, const TextureParameter &param);
        Ref<Texture> Load(const std::array<std::string_view, 6> &pathes);

        static void WriteToFile(const Texture &texture, const std::string &path);
    };
} // namespace fts

#endif // __TEXTURELOADER_H__
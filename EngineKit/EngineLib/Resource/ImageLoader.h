#ifndef __IMAGELOADER_H__
#define __IMAGELOADER_H__


#include "Graphics/Image.h"

namespace fts
{
class  ImageLoader {
   public:
    Ref<ByteImage> Load(const std::string_view &path);
    Ref<ByteImage> Load(const uint8_t *data, int32_t size);
};

} // namespace fts



#endif // __IMAGELOADER_H__
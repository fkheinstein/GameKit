#ifndef __GLTRANSLATOR_H__
#define __GLTRANSLATOR_H__

#include <GL/glew.h>
#include "Graphics/Graphics.h"

namespace fts
{
        GLenum Translate(BufferLayoutType data_type);

        GLenum Translate(MeshTopology mesh_type);

        GLenum Translate(PolygonMode mode);

        GLint Translate(BufferIOType io_type);

        GLenum Translate(DataFormat format);

        GLenum Translate(TextureType type, MultiSampleLevel msaa);

        GLint  Translate(TextureWrap wrap);

        GLint  Translate(TextureMagFilter filter);

        GLint  Translate(TextureMinFilter filter, MipmapMode mode);

        GLenum  Translate(Operation operation);

        GLenum  Translate(Face face);

        GLenum  Translate(BlitFilter filter);

        GLint  Translate(BufferBitMask bit);

        GLenum  Translate(DepthFunc depth_func);

        GLenum  Translate(Access access);

        GLenum  Translate(BarrierBit bit);

        GLenum  GetFormatType(DataFormat format);
        GLenum  GetDataType(DataFormat format);



} // namespace fts


#endif // __GLTRANSLATOR_H__
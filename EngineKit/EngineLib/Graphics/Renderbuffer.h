#ifndef __RENDERBUFFER_H__
#define __RENDERBUFFER_H__

#include "Graphics/Texture.h"

namespace fts
{
    class Renderbuffer
    {
    public:
        static Ref<Renderbuffer> Create(int32_t width, int32_t height, MultiSampleLevel samples, DataFormat format);

        virtual uint32_t Handle() const = 0;

        int32_t GetWidth() const { return m_width; }
        int32_t GetHeight() const { return m_height; }
        MultiSampleLevel GetSamples() const { return m_samples; }

        DataFormat GetFormat() const { return m_format; }

    protected:
        Renderbuffer(int32_t width, int32_t height, MultiSampleLevel samples, DataFormat format);

        int32_t m_width;
        int32_t m_height;
        MultiSampleLevel m_samples;

        DataFormat m_format;
    };
} // namespace fts

#endif // __RENDERBUFFER_H__
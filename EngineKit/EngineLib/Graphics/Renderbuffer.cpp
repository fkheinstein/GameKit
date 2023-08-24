#include <spch.h>

#include "Graphics/Renderbuffer.h"

#include "Graphics/Device.h"
#include "Graphics/OpenGL/GLRenderbuffer.h"


namespace fts
{
    Ref<Renderbuffer> Renderbuffer::Create(int32_t width, int32_t height, MultiSampleLevel samples, DataFormat format)
    {
        Ref<Renderbuffer> texture;
        switch (Device::GetAPI()) {
        case Device::API::OpenGL:
            texture = CreateRef<GLRenderbuffer>(width, height, samples, format);
            break;
        default:
            FTS_CORE_ERROR("Unsupported API!");
            break;
        }

        return texture;
    }

    Renderbuffer::Renderbuffer(int width, int height, MultiSampleLevel samples, DataFormat format)
        : m_width(width), m_height(height), m_samples(samples), m_format(format)
    {
    }

} // namespace fts

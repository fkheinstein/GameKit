#include <spch.h>


#include "Graphics/Buffer.h"
#include "Graphics/Graphics.h"
#include "Graphics/Device.h"
#include "Graphics/OpenGL/GLDevice.h"
#include "Graphics/OpenGL/GLBuffer.h"
#include "Graphics/OpenGL/GLTexture.h"


namespace fts
{
    Ref<VertexBuffer> VertexBuffer::Create(const void *data, size_t size, BufferIOType io)
    {
        Ref<VertexBuffer> vb;
        switch (Device::GetAPI())
        {
        case Device::API::OpenGL:
            vb = CreateRef<GLVertexBuffer>(data, size, io);
            break;
        default:
            FTS_CORE_ERROR("Unsupported API!");
            break;
        }
        return vb;
    }

    Ref<IndexBuffer> IndexBuffer::Create(const uint32_t *data, uint32_t count, BufferIOType io)
    {
        Ref<IndexBuffer> eb;
        switch (Device::GetAPI())
        {
        case Device::API::OpenGL:
            eb = CreateRef<GLIndexBuffer>(data, count, io);
            break;
        default:
            FTS_CORE_ERROR("Unsupported API!");
            break;
        }
        return eb;
    }

    Ref<UniformBuffer> UniformBuffer::Create(const void *data, size_t size, BufferIOType io)
    {
        Ref<UniformBuffer> ub;
        switch (Device::GetAPI())
        {
        case Device::API::OpenGL:
            ub = CreateRef<GLUniformBuffer>(data, size, io);
            break;
        default:
            FTS_CORE_ERROR("Unsupported API!");
            break;
        }
        return ub;
    }

    IndexBuffer::IndexBuffer(uint32_t count) : m_count(count) {}

    uint32_t IndexBuffer::GetCount() const { return m_count; }

} // namespace fts

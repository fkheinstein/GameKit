#ifndef __BUFFER_H__
#define __BUFFER_H__


#include <Core/Base.h>
#include <Graphics/Graphics.h>


namespace fts
{
    class Buffer
    {
    public:
        virtual ~Buffer() = default;

        Buffer(const Buffer &) = delete;

        Buffer &operator=(const Buffer &) = delete;

        virtual void UpdateData(const void *data, size_t size,  size_t offset = 0) = 0;

        virtual uint32_t Handle() const = 0;

    protected:
        Buffer() = default;
    };

    class VertexBuffer : virtual public Buffer
    {
    public:
        static Ref<VertexBuffer> Create(const void *data, size_t size, BufferIOType io);
        virtual ~VertexBuffer() = default;

    protected:
        VertexBuffer() = default;
    };

    class IndexBuffer : virtual public Buffer
    {
    public:
        static Ref<IndexBuffer> Create(const uint32_t *data, uint32_t count,  BufferIOType io);
        virtual ~IndexBuffer() = default;

        uint32_t GetCount() const;

    protected:
        IndexBuffer(uint32_t count);

        uint32_t m_count;
    };

    class UniformBuffer : virtual public Buffer
    {
    public:
        static Ref<UniformBuffer> Create(const void *data, size_t size,  BufferIOType io);
        virtual ~UniformBuffer() = default;

        virtual uint32_t GetBindingPoint() const = 0;

    protected:
        UniformBuffer() = default;
    };
} // namespace fts

#endif // __BUFFER_H__
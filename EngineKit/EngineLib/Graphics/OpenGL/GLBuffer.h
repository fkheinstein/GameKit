#ifndef __GLBUFFER_H__
#define __GLBUFFER_H__


#include "Core/Base.h"
#include "Graphics/Buffer.h"



namespace fts
{
    class GLBuffer : virtual public Buffer {
    public:
        void UpdateData(const void* data, size_t size, size_t offset) override;

        uint32_t Handle() const override { return m_id; }

    protected:
        GLBuffer(GLenum type, GLenum io, const void* data, size_t size);

        virtual ~GLBuffer();

    protected:
        GLenum m_type;
        GLenum m_io;

        size_t m_size;
        GLuint m_id;
    };

    class GLVertexBuffer : public VertexBuffer, public GLBuffer {
    public:
        GLVertexBuffer(const void* data, size_t size, BufferIOType io);

        ~GLVertexBuffer() = default;
    };

    class GLIndexBuffer : public IndexBuffer, public GLBuffer {
    public:
        GLIndexBuffer(const uint32_t* data, uint32_t count, BufferIOType io);

        void UpdateData(const void* data, size_t size, size_t offset) override;

        ~GLIndexBuffer() = default;
    };

    class GLUniformBuffer : public UniformBuffer, public GLBuffer {
    public:
        GLUniformBuffer(const void* data, size_t size, BufferIOType io);
        ~GLUniformBuffer() = default;

        uint32_t GetBindingPoint() const override;

    private:
        uint32_t m_base;
        static uint32_t s_count;
    };


} // namespace fts


#endif // __GLBUFFER_H__
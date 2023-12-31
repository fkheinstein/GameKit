#ifndef __GLVERTEXARRAY_H__
#define __GLVERTEXARRAY_H__

#include "Core/Base.h"
#include "Graphics/VertexArray.h"
#include "Graphics/BufferLayout.h"
#include "Graphics/OpenGL/GLBuffer.h"


namespace fts
{

    class  GLVertexArray : public VertexArray
    {
    public:
        GLVertexArray();
        ~GLVertexArray();


        GLVertexArray(const GLVertexArray&) = delete;
        GLVertexArray(GLVertexArray&&) = delete;
        GLVertexArray& operator = (const GLVertexArray&) = delete;
        GLVertexArray& operator = (GLVertexArray&&) = delete;


        void BindVertexBuffer(const VertexBuffer& buffer, int32_t index) override;
        void AddBufferLayout(const VertexBufferLayout& layout) override;

        void BindIndexBuffer(const IndexBuffer& buffer) override;

        uint32_t Handle() const override { return m_id; }

        void Bind() const  override;
        void Unbind() const override;


    private:
        std::vector<VertexBufferLayout> m_layouts;

        uint32_t m_id;
        uint32_t m_attrib_id;
    };


} // namespace fts


#endif // __GLVERTEXARRAY_H__
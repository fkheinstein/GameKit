#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include "Core/Base.h"
#include "Graphics/BufferLayout.h"
#include "Graphics/Buffer.h"

namespace fts
{

    class VertexArray {
    public:
        static Ref<VertexArray> Create();

        virtual ~VertexArray() = default;

        VertexArray(const VertexArray&) = delete;

        VertexArray& operator=(const VertexArray&) = delete;

        virtual uint32_t Handle() const = 0;

        virtual void BindVertexBuffer(const VertexBuffer& buffer, int index) = 0;
        virtual void AddBufferLayout(const VertexBufferLayout& layout) = 0;

        virtual void BindIndexBuffer(const IndexBuffer& buffer) = 0;

    protected:
        VertexArray() = default;
    };
} // namespace fts


#endif // __VERTEXARRAY_H__
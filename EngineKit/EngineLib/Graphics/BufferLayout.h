#ifndef __BUFFERLAYOUT_H__
#define __BUFFERLAYOUT_H__


#include <string>
#include <vector>

#include "Core/Base.h"
#include "Graphics/Graphics.h"


namespace fts
{
    struct VertexBufferLayoutElement
    {
        BufferLayoutType type;
        uint32_t count;
        size_t offset;
        bool normalized;
    };

    class  VertexBufferLayout
    {
    public:
        VertexBufferLayout(uint32_t instance_stride = 0);

        void Push(BufferLayoutType type, bool normalized = false);

        void Clear();

        const std::vector<VertexBufferLayoutElement> &GetElements() const;

        uint32_t GetInstanceStride() const { return m_instance_stride; }
        uint32_t GetStride() const;

    private:
        std::vector<VertexBufferLayoutElement> m_elements;
        uint32_t m_stride;
        uint32_t m_instance_stride;
    };
} // namespace fts




#endif // __BUFFERLAYOUT_H__
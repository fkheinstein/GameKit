#ifndef __MESH_H__
#define __MESH_H__


#include "Graphics/VertexArray.h"

namespace fts
{

    struct  Vertex {
        glm::vec3 position;
        glm::vec2 uv;
        glm::vec3 normal;
        glm::vec3 tangent;
        glm::vec3 bi_tangent;
    };

    class Mesh {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, MeshTopology topology);

        void Update();
        void Clear();

        void SetVerices(const std::vector<Vertex>& vertices);
        void SetIndices(const std::vector<uint32_t>& indices);

        VertexBuffer* GetVertexBuffer() const;
        IndexBuffer* GetIndexBuffer() const;

        void SetTopology(MeshTopology topology);
        MeshTopology GetTopology() const { return m_topology; }

        void SetPolygonMode(PolygonMode wireframe);
        PolygonMode GetPolygonMode() const;

        const std::vector<Vertex>& GetVertices() const;
        std::vector<Vertex>& GetVertices();

    private:
        std::vector<Vertex> m_vertices;
        std::vector<uint32_t> m_indices;
        MeshTopology m_topology;
        Ref<VertexBuffer> m_vertexBuffer;
        Ref<IndexBuffer> m_indexBuffer;
        PolygonMode m_polygonMode;
    };



    template <typename vertexT = Vertex>
    class MeshT
    {
    public:
        MeshT(const std::vector<vertexT>& vertices,  const std::vector<uint32_t>& indices, MeshTopology topology)
            : m_vertices(vertices)
            , m_indices(indices)
            , m_topology(topology)
            , m_polygonMode(PolygonMode::Fill)
        {
            m_vertexBuffer = VertexBuffer::Create(m_vertices.data(), m_vertices.size() * sizeof(vertexT), BufferIOType::Dynamic);
            m_indexBuffer = IndexBuffer::Create(m_indices.data(), m_indices.size(), BufferIOType::Dynamic);
        }

        void SetVerices(const std::vector<vertexT>& vertices) {  m_vertices = vertices;  }
        void SetIndices(const std::vector<uint32_t>& indices) {  m_indices = indices;  }

        const std::vector<vertexT>& GetVertices() const { return m_vertices; }
        std::vector<vertexT>& GetVertices() { return m_vertices; }

        void SetTopology(MeshTopology topology);
        MeshTopology GetTopology() const { return m_topology; }

        void SetPolygonMode(PolygonMode wireframe);
        PolygonMode GetPolygonMode() const;

        void Update()
        {
            m_indexBuffer->UpdateData(m_indices.data(), m_indices.size() * sizeof(uint32_t));
            m_vertexBuffer->UpdateData(m_vertices.data(), m_vertices.size() * sizeof(vertexT));
        }


        void Clear()
        {
            m_vertices.clear();
            m_indices.clear();
        }

    private:
        std::vector<vertexT> m_vertices;
        std::vector<uint32_t> m_indices;

        Ref<VertexBuffer> m_vertexBuffer;
        Ref<IndexBuffer> m_indexBuffer;
        MeshTopology m_topology;
        PolygonMode m_polygonMode;
    };

} // namespace fts


#endif // __MESH_H__
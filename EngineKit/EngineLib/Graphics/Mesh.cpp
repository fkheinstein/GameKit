#include <spch.h>


#include "Mesh.h"

namespace fts {

    Mesh::Mesh(const std::vector<Vertex>& vertices,
        const std::vector<uint32_t>& indices, MeshTopology topology)
        : m_vertices(vertices),
        m_indices(indices),
        m_topology(topology),
        m_polygonMode(PolygonMode::Fill)
    {
        m_vertexBuffer = VertexBuffer::Create(m_vertices.data(),   m_vertices.size() * sizeof(Vertex),   BufferIOType::Dynamic);
        m_indexBuffer = IndexBuffer::Create(m_indices.data(), m_indices.size(),  BufferIOType::Dynamic);
    }

    void Mesh::SetVerices(const std::vector<Vertex>& vertices)
    {
        m_vertices = vertices;
    }

    void Mesh::SetIndices(const std::vector<uint32_t>& indices)
    {
        m_indices = indices;
    }

    void Mesh::Update()
    {
        m_indexBuffer->UpdateData(m_indices.data(),  m_indices.size() * sizeof(uint32_t));
        m_vertexBuffer->UpdateData(m_vertices.data(),  m_vertices.size() * sizeof(Vertex));
    }


    void Mesh::Clear()
    {
        m_vertices.clear();
        m_indices.clear();
    }

    VertexBuffer* Mesh::GetVertexBuffer() const { return m_vertexBuffer.get(); }
    IndexBuffer* Mesh::GetIndexBuffer() const { return m_indexBuffer.get(); }

    
    void Mesh::SetTopology(MeshTopology topology) { m_topology = topology; }

    void Mesh::SetPolygonMode(PolygonMode polygonMode)
    {
        m_polygonMode = polygonMode;
    }

    PolygonMode Mesh::GetPolygonMode() const { return m_polygonMode; }

    const std::vector<Vertex>& Mesh::GetVertices() const { return m_vertices; }
    std::vector<Vertex>& Mesh::GetVertices() { return m_vertices; }

}
#ifndef __MODEL_H__
#define __MODEL_H__



#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/ModelNode.h"
#include <vector>

namespace fts
{
    class Mesh;
    class ModelNode;
    class Material;
    class Model
    {
    public:
        using ImportedTexture = std::unordered_map<std::string, Ref<Texture>>;
        Model() = default;
        virtual ~Model() { delete m_root_node; };

        void SetRootNode(ModelNode* node) { m_root_node = node; }
        ModelNode* GetRootNode() const { return m_root_node; }

        void AddMaterial(Material&& material)
        {
            m_materials.push_back(std::move(material));
        }
        const Material& GetMaterial(int32_t id) const { return m_materials.at(id); }

        void AddMesh(Mesh&& mesh) { m_meshes.push_back(std::move(mesh)); }
        const Mesh& GetMesh(int32_t id) const { return m_meshes.at(id); }

        ImportedTexture& GetImportedTextures()
        {
            return m_textures;
        }

    private:
        ModelNode* m_root_node;
        std::vector<Mesh> m_meshes;
        std::vector<Material> m_materials;
        ImportedTexture m_textures;
    };

} // namespace fts

#endif // __MODEL_H__
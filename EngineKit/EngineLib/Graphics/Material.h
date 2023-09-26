#ifndef __MATERIAL_H__
#define __MATERIAL_H__

namespace fts
{

    class Texture;
    using Vector3f = glm::vec3;
    using Matrix4f = glm::mat4;

    enum class MaterialType
    {
        None,
        Diffuse,
        Specular,
        Ambient,
        Emissive,
        Normal,
        Shininess
    };

    const std::string GetMaterialName(MaterialType type);

    class Material
    {
    public:
        Material();
        void SetTexture(MaterialType type, Texture *texture);
        const Texture *GetTexture(MaterialType type) const;

        void SetAmbientColor(const Vector3f &color) { m_ambient_base = color; }
        void SetDiffuseColor(const Vector3f &color) { m_diffuse_base = color; }
        void SetEmissiveColor(const Vector3f &color) { m_emissive_base = color; }
        const Vector3f &GetAmbientColor() const { return m_ambient_base; }
        const Vector3f &GetDiffuseColor() const { return m_diffuse_base; }
        const Vector3f &GetEmissiveColor() const { return m_emissive_base; }

        // SERIALIZE(m_diffuse_base, m_ambient_base, m_emissive_base)
    private:
        std::unordered_map<MaterialType, Texture *> m_textures;
        Vector3f m_diffuse_base;
        Vector3f m_ambient_base;
        Vector3f m_emissive_base;
    };
} // namespace fts

#endif // __MATERIAL_H__
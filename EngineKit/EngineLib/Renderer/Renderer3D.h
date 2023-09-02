#ifndef __RENDERER3D_H__
#define __RENDERER3D_H__


#include "Renderer/Renderer.h"

namespace fts
{
    class CascadeShadow;
    class Mesh;
    class Material;

    struct  ShadowData {
        glm::mat4 projection_view[16];
    };


    class Renderer3D : protected Renderer {
    public:
        static void Init();
        static void Reset();
        static std::string GetDebugInfo();

        static void SetCascadeShadow(const CascadeShadow& shadow);
        static void BindCascadeShadow(Shader& shader);

        static void DrawMesh(const Shader& shader, const Mesh& mesh);
        static void SetMaterial(Shader& shader, const Material& material);
    };

} // namespace fts

#endif // __RENDERER3D_H__
#ifndef __LIGHT_H__
#define __LIGHT_H__

namespace fts
{
    using Vector2f = glm::vec2;
    using Vector3f = glm::vec3;
    using Vector4f = glm::vec4;

    struct DirectionalLight {
        Vector3f ambient;
        Vector3f diffuse;
        Vector3f specular;
    };

    struct  PointLight {
        Vector3f ambient;
        Vector3f diffuse;
        Vector3f specular;
        float constant{ 1.0 };
        float linear{ 0.1 };
        float quadratic{ 0.01 };
    };

} // namespace fts


#endif // __LIGHT_H__
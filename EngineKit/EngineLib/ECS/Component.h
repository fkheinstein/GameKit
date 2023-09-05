#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Core/Base.h"
#include "Utils/ResourceId.h"

#include "Graphics/Model.h"
#include "Graphics/Font.h"
#include "Graphics/Light.h"

#include "Graphics/Camera.h"
#include "Graphics/CascadeShadow.h"
#include "Graphics/PointShadow.h"


#include "Utils/Transform.h"

#include "ECS/Scene.h"

namespace fts
{


    using Vector2f = glm::vec2;
    using Vector3f = glm::vec3;
    using Vector4f = glm::vec4;

    using Matrix4f = glm::mat4;
    using Quaternion = glm::quat;



    struct IdComponent {
        ResourceId id;
    };

    struct TagComponent {
        std::string tag;
    };


    struct TransformComponent {
        std::set<EntityId> children;
        EntityId parent;
        entt::registry* ecs{ nullptr };

        TransformComponent();

        void SetLocalPosition(const Vector3f& position);
        void SetLocalRotation(const Quaternion& rotation);
        void SetLocalScale(const Vector3f& scale);
        void SetLocalTransform(const Matrix4f& transform);

        Vector3f GetLocalPosition() const;
        Quaternion GetLocalRotation() const;
        Vector3f GetLocalScale() const;
        const Transform& GetLocalTransform() const;

        void SetWorldPosition(const Vector3f& position);
        void SetWorldRotation(const Quaternion& rotation);
        void SetWorldScale(const Vector3f& scale);
        void SetWorldTransform(const Matrix4f& transform);

        Vector3f GetWorldPosition() const;
        Quaternion GetWorldRotation() const;
        Vector3f GetWorldScale() const;
        const Transform& GetWorldTransform() const;

        Vector3f GetLocalRight() const;
        Vector3f GetLocalUp() const;
        Vector3f GetLocalFront() const;

        Vector3f GetWorldRight() const;
        Vector3f GetWorldUp() const;
        Vector3f GetWorldFront() const;

        void UpdateGlobalPosition();
        void UpdateGlobalRotation();
        void UpdateGlobalScale();

        void UpdateLocalPosition();
        void UpdateLocalRotation();
        void UpdateLocalScale();

    private:
        Transform m_world_transform;
        Transform m_local_transform;
    };

    struct MeshComponent {
        ResourceId model_id;
        uint32_t mesh_index;
        Material material;
    };

    struct DirectionalLightComponent {
        DirectionalLight light;
        CascadeShadow shadow;
        bool is_cast_shadow{ false };

    };

    struct  PointLightComponent {
        PointLight light;
        PointShadow shadow;
        bool is_cast_shadow{ false };

    };

    struct TextComponent {
        ResourceId font_id;
        Vector4f color = Vector4f(1);
        std::string text;

    };

    struct CameraComponent {
        Camera* camera{nullptr};
        bool primary{ true };
        CameraComponent() = default;        
        CameraComponent(float fov, float width, float height,  float near_z, float far_z) //: camera(type, fov, width, height, near_z, far_z)
        {
        }
    };

    struct SpriteFrame {
        ResourceId texture_id;
        std::array<Vector2f, 2> uvs{ Vector2f(0), Vector2f(1) };
        Vector2f size{ 10.0f };
        int priority{ 0 };
    };

    struct SpriteComponent {
        SpriteFrame frame;

    };

    /*struct SpriteAnimationComponent {
        std::vector<FrameAnimation<SpriteFrame>> animations;
        Animator<FrameAnimation<SpriteFrame>> animator;

    };*/

    template <>
    inline void OnComponentAdded<TransformComponent>(entt::registry& reg,
        entt::entity ent)
    {
        auto& data = reg.get<TransformComponent>(ent);
        data.ecs = &reg;
    }

    /*template <>
    inline void OnComponentAdded<SpriteAnimationComponent>(entt::registry& reg,
        entt::entity ent)
    {
        auto& anim = reg.get<SpriteAnimationComponent>(ent);
        anim.animations.push_back(FrameAnimation<SpriteFrame>());
    }*/

    template <>
    inline void OnComponentAdded<DirectionalLightComponent>(entt::registry& reg,
        entt::entity ent)
    {
        auto& light = reg.get<DirectionalLightComponent>(ent);
        if (light.is_cast_shadow) {
            light.shadow.CreateShadowMap();
        }
    }

    template <>
    inline void OnComponentAdded<PointLightComponent>(entt::registry& reg,
        entt::entity ent)
    {
        auto& light = reg.get<PointLightComponent>(ent);
        if (light.is_cast_shadow) {
            light.shadow.CreateShadowMap();
        }
    }

    
} // namespace fts



#endif // __COMPONENT_H__
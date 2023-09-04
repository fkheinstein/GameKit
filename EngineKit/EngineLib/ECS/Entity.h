#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Core/Base.h"
#include "ECS/Scene.h"

namespace fts
{
    class Entity {
    public:
        Entity();
        Entity(entt::entity handle, Scene* scene);

        void Destroy(bool is_root = true);

        void AddChild(Entity& child);

        void RemoveChild(Entity& child);

        template <typename T, typename... Args>
        T& AddComponent(Args &&...args);

        template <typename T>
        bool HasComponent() const;

        template <typename T>
        void RemoveComponent();

        template <typename T>
        T& GetComponent();

        template <typename T>
        const T& GetComponent() const;

        operator bool() const;
        operator entt::entity() const;

        bool operator==(const Entity& other) const;
        bool operator!=(const Entity& other) const;

        bool operator<(const Entity& other) const;

        Scene* GetScene() const { return m_scene; }

        EntityId Handle() const { return m_handle; }

    private:
        EntityId m_handle;
        Scene* m_scene;
    };

    template <typename T, typename... Args>
    T& Entity::AddComponent(Args &&...args)
    {
        FTS_ASSERT_MSG(!HasComponent<T>(), "Entity already has this component!");

        T& component = m_scene->emplace<T>(m_handle, std::forward<Args>(args)...);
        return component;
    }

    template <typename T>
    bool Entity::HasComponent() const
    {
        return m_scene->all_of<T>(m_handle);
    }

    template <typename T>
    void Entity::RemoveComponent()
    {
        FTS_ASSERT_MSG(HasComponent<T>(), "Entity does not have this component!");
        m_scene->remove<T>(m_handle);
    }

    template <typename T>
    T& Entity::GetComponent()
    {
        FTS_ASSERT_MSG(HasComponent<T>(), "Entity does not have this component!");
        return m_scene->get<T>(m_handle);
    }

    template <typename T>
    const T& Entity::GetComponent() const
    {
        FTS_ASSERT_MSG(HasComponent<T>(), "Entity does not have this component!");
        return m_scene->get<T>(m_handle);
    }

    
} // namespace fts



#endif // __ENTITY_H__
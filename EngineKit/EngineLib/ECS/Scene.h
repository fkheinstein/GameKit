#ifndef __SCENE_H__
#define __SCENE_H__

#include "Core/Base.h"

#include "entt/entt.hpp"


namespace fts
{
    using EntityId = entt::entity;
    using EntityIdType = entt::id_type;
    class Entity;

    //using ComponentSerializeFunction = entt::delegate<void(entt::snapshot&, cereal::PortableBinaryOutputArchive&)>;
    //using ComponentDeserializeFunction = entt::delegate<void(entt::snapshot_loader&, cereal::PortableBinaryInputArchive&)>;

    template <typename T>
    void OnComponentAdded(entt::registry&, entt::entity)  {   }

    class Scene : public entt::registry {
    public:
        Scene(std::string name);
        ~Scene() = default;

        std::string name;

        Entity CreateEntity(const std::string& name);

        //void Serialize(cereal::PortableBinaryOutputArchive& archive) const;
        //void Deserialize(cereal::PortableBinaryInputArchive& archive);

        Entity CloneEntity(EntityId from);

        // Registering a component enables serialization as well as duplication
        // functionality in & out editor.
        template <typename T>
        void RegisterComponent()
        {
            auto id = entt::type_hash<T>::value();
            //m_serialize_functions[id].first.template connect<&Scene::SerializeComponent<T>>();
            //m_serialize_functions[id].second.template connect<&Scene::DeserializeComponent<T>>();
            on_construct<T>().template connect<&OnComponentAdded<T>>();
        }

    private:
    
        template <typename T>
        void CloneComponent(EntityId from, EntityId to)
        {
            T component = get<T>(from);
            emplace<T>(to, component);
        }

    };


    
} // namespace fts



#endif // __SCENE_H__
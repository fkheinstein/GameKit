#ifndef __SCRIPTMANAGER_H__
#define __SCRIPTMANAGER_H__



//#include "Entity.hpp"
#include "Script.h"

#include <memory>
#include <unordered_map>
#include <utility>


namespace fts
{

    class Entity
    {
    public:
        Entity();
        ~Entity();

    private:

    };


    class ScriptManager {
    public:
        void add(Entity entity, std::shared_ptr<ScriptBase> script) { m_EntityScript[entity] = script; }

        template <typename TScript, typename = std::enable_if_t<std::is_base_of_v<ScriptBase, TScript>>>
        const std::shared_ptr<TScript> get(Entity entity) {
            auto it = m_EntityScript.find(entity);
            if (it == m_EntityScript.end()) {
                return nullptr;
            }

            return std::dynamic_pointer_cast<TScript>(it->second);
        }

        void remove(Entity entity) { m_EntityScript.erase(entity); }

    private:
        std::unordered_map<Entity, std::shared_ptr<ScriptBase>> m_EntityScript;
    };


    Entity::Entity()
    {
    }

    Entity::~Entity()
    {
    }


} // namespace fts

#endif // __SCRIPTMANAGER_H__
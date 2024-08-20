#pragma once
#include <queue>
#include <array>
#include <stdint.h>
#include <cassert>
#include "core/ECS/ecs.hpp"

namespace Temporal::Core::ECS
{
    // manages all entities and its component signatures
    class Entity_Manager
    {
    public:
        Entity_Manager()
        {
            m_entities_name.reserve(MAX_ENTITIES);
            for (Entity e = 0; e < MAX_ENTITIES; ++e)
            {
                m_available_entities.push(e);
            }
        }

        Entity Create_Entity(const char *name)
        {
            // assert(m_living_entities_counter < MAX_ENTITIES && "Too many entities");

            Entity nextId = m_available_entities.front();
            m_available_entities.pop();
            m_living_entities_counter++;

            m_entities_name.push_back(name);

            return nextId;
        }

        const char *Get_Entity_Name(Entity e)
        {
            return m_entities_name[e];
        }

        void Destroy_Entity(Entity e)
        {
            m_component_signatures[e].reset();
            m_available_entities.push(e);
            m_entities_name.erase(m_entities_name.begin() + e);
            m_living_entities_counter--;
        }

        // gets the component signature from a entity
        Component_Signature Get_Signature(Entity e)
        {
            return m_component_signatures[e];
        }

        // sets the component signature of a entity
        void Set_Component_Signature(Entity e, Component_Signature signature)
        {
            m_component_signatures[e] = signature;
        }
        // association between component signatures and entities
        std::array<Component_Signature, MAX_ENTITIES> m_component_signatures{};

        // unused entities, no components associated
        std::queue<Entity> m_available_entities{};

        std::vector<const char *> m_entities_name;
        uint32_t m_living_entities_counter;
    };

}
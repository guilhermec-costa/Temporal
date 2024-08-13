#pragma once
#include "core/ECS/ecs.hpp"
#include <queue>
#include <array>
#include <stdint.h>
#include <cassert>

namespace Temporal::Core::ECS
{
    class Entity_Manager
    {
        public:
            Entity_Manager()
            {
                for(Entity e=0; e < MAX_ENTITIES; ++e)
                {
                    m_available_entities.push(e);
                }
            }

            Entity Create_Entity()
            {
                assert(m_living_entities_counter < MAX_ENTITIES && "Too many entities");

                Entity nextId = m_available_entities.front();
                m_available_entities.pop();
                m_living_entities_counter++;

                return nextId;
            }

            void Destroy_Entity(Entity e)
            {
                m_component_signatures[e].reset();
                m_available_entities.push(e);
                --m_living_entities_counter;
            }

            Component_Signature Get_Signature(Entity e)
            {
                return m_component_signatures[e];
            }

            void Set_Component_Signature(Entity e, Component_Signature signature)
            {
                m_component_signatures[e] = signature;
            }
    };

    std::queue<Entity> m_available_entities{};
    std::array<Component_Signature, MAX_ENTITIES> m_component_signatures{};
    uint32_t m_living_entities_counter;
}
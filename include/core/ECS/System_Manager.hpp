#pragma once
#include <memory>
#include <unordered_map>
#include "core/ECS/System.hpp"
#include "core/ECS/ecs.hpp"

namespace Temporal::Core::ECS {
    // Maintain a record of registered systems and their signatures.
    class System_Manager
    {
        public:

        template<typename T>

            // associates a system with a system name
            std::shared_ptr<T> Register_System()
            {
                const char* type_name = typeid(T).name;
                std::shared_ptr<T> system = std::make_shared<T>();
                m_systems.insert(std::make_pair(type_name, system));
                return system;
            }

            template<typename T>
            void Set_Signature(Component_Signature signature)
            {
                const char* type_name = typeid(T).name;
                m_signatures.insert(std::make_pair(type_name, signature));
            }

            void Entity_Destroyed_Event(Entity e)
            {
                for(const auto& pair : m_systems)
                {
                    auto const& system = pair.second;
                    system->m_entites.erase(e);
                }
            }

            void Entity_Signature_Changed_Event(Entity entity, Component_Signature entity_signature)
            {
                for(const auto& pair : m_systems)
                {
                    const auto& type = pair.first;
                    const auto& system = pair.second;
                    const auto& system_signature = m_signatures[type];

                    if((entity_signature & system_signature) == system_signature)
                    {
                        system->m_entites.insert(entity);
                    }
                    else
                    {
                        system->m_entites.erase(entity);
                    }
                }
            }

        private:
            std::unordered_map<const char*, std::shared_ptr<System>> m_systems;

            // the signature that the system will operate on
            std::unordered_map<const char*, Component_Signature> m_signatures;
    };
}
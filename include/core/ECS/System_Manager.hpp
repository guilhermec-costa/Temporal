#pragma once
#include <memory>
#include <unordered_map>
#include <algorithm>
#include "core/ECS/System.hpp"

namespace Temporal::Core::ECS
{
    // Maintain a record of registered systems and their signatures.
    class System_Manager
    {
    public:
        template <typename T>

        // associates a system with a system name
        std::shared_ptr<T> Register_System()
        {
            const char *type_name = typeid(T).name();
            std::shared_ptr<T> system = std::make_shared<T>();
            m_systems.insert(std::make_pair(type_name, system));
            return system;
        }

        template <typename T>
        void Set_Signature(Component_Signature signature)
        {
            const char *type_name = typeid(T).name();
            m_signatures.insert(std::make_pair(type_name, signature));
        }

        // removes a given entity from the entities that this system is responsible for
        void Entity_Destroyed_Event(Entity e)
        {
            for (const auto &pair : m_systems)
            {
                auto const &system = pair.second;
                auto it = std::find(system->m_entites.begin(), system->m_entites.end(), e);
                if (it != system->m_entites.end())
                {
                    system->m_entites.erase(it);
                }
            }
        }

        void Entity_Signature_Changed_Event(Entity entity, Component_Signature entity_signature)
        {
            for (auto const &pair : m_systems)
            {
                auto const &type = pair.first;
                auto const &system = pair.second;
                auto const &system_signature = m_signatures[type];

                if ((entity_signature & system_signature) == system_signature)
                {
                    // system->m_entites.insert(entity);
                    system->m_entites.push_back(entity);
                }
                else
                {
                    // system->m_entites.erase(entity);
                    auto it = std::find(system->m_entites.begin(), system->m_entites.end(), entity);
                    if (it != system->m_entites.end())
                    {
                        system->m_entites.erase(it);
                    }
                }
            }
        }

    private:
        // map from a system name to a system pointer
        std::unordered_map<const char *, std::shared_ptr<System>> m_systems{};

        // map from a system name to a component signature
        std::unordered_map<const char *, Component_Signature> m_signatures{};
    };
}
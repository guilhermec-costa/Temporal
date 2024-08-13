#pragma once
#include <memory>
#include "core/ECS/Entity_Manager.hpp"
#include "core/ECS/Component_Manager.hpp"
#include "core/ECS/System_Manager.hpp"

namespace Temporal::Core::ECS {
    class ECS_Orchestrator
    {
        public:
            ECS_Orchestrator() = default;
            void Init()
            {
                m_entity_manager = std::make_unique<Entity_Manager>();
                m_component_manager = std::make_unique<Component_Manager>();
                m_system_manager = std::make_unique<System_Manager>();
            }

            void Create_Entity()
            {
                m_entity_manager->Create_Entity();
            }

            void Destroy_Entity(Entity entity)
            {
                m_entity_manager->Destroy_Entity(entity);
                m_component_manager->Entity_Destroyed_Event(entity);
                m_system_manager->Entity_Destroyed_Event(entity);
            }

            template<typename T>
            void Register_Component()
            {
                m_component_manager->Register_Component<T>();
            }

            template<typename T>
            void Add_Component(Entity entity, T component)
            {
                m_component_manager->Add_Component<T>(entity, component);
                auto signature = m_entity_manager->Get_Signature(entity);
                signature.set(m_component_manager->Get_Component_Type<T>(), true);
                m_entity_manager->Set_Component_Signature(entity, signature);
                m_system_manager->Entity_Signature_Changed_Event(entity, signature);
            }

            template<typename T>
            void Remove_Component(Entity entity)
            {
                m_component_manager->Remove_Component<T>(entity);
                auto signature = m_entity_manager->Get_Signature(entity);
                m_entity_manager->Set_Component_Signature(entity, signature);
                m_system_manager->Entity_Signature_Changed_Event(entity, signature);
            }

            template<typename T>
            T& Get_Component(Entity entity)
            {
                return m_component_manager->Get_Component<T>(entity);
            }

            template<typename T>
            Component_Type Get_Component_Type()
            {
                return m_component_manager->Get_Component_Type<T>();
            }

            template<typename T>
            std::shared_ptr<T> Register_System()
            {
                return m_system_manager->Register_System<T>();
            }

            template<typename T>
            void Set_System_Signature(Component_Signature signature)
            {
                m_system_manager->Set_Signature<T>(signature);
            }

        private:
            std::unique_ptr<Component_Manager> m_component_manager;
            std::unique_ptr<Entity_Manager> m_entity_manager;
            std::unique_ptr<System_Manager> m_system_manager;
    };
}

using ECS_Orchestrator = Temporal::Core::ECS::ECS_Orchestrator;
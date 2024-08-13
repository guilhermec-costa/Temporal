#pragma once
#include <unordered_map>
#include <memory>
#include "core/ECS/ecs.hpp"
#include "core/ECS/Component_Array.hpp"

namespace Temporal::Core::ECS
{
    class Component_Manager
    {
    public:
        template <typename T>
        void Register_Component()
        {
            const char *type_name = typeid(T).name;
            m_component_types.insert(std::make_pair(type_name, m_next_component_type));
            m_component_arrays.insert(std::make_pair(type_name, std::make_shared<Component_Array<T>>())) : m_next_component_type++;
        }

        template <typename T>
        Component_Type Get_Component_Type()
        {
            const char *type_name = typeid(T).name;

            // used for creating component signatures
            return m_component_types[type_name];
        }

        template<typename T>
        void Add_Component(Entity e, T component)
        {
            Get_Component_Array<T>()->Insert_Data(e, component);
        }

    private:
        std::unordered_map<const char *, Component_Type> m_component_types{};
        std::unordered_map<const char *, std::shared_ptr<IComponent_Array>> m_component_arrays{};
        Component_Type m_next_component_type{};

        template <typename T>
        std::shared_ptr<Component_Array<T>> Get_Component_Array()
        {
            const char *type_name = typeid(T).name;
            // converts IComponentArray to Component_Array<T>
            return std::static_pointer_cast<Component_Array<T>>(m_component_arrays[type_name]);
        }
    };
}
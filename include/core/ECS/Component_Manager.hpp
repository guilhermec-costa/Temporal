#pragma once
#include <unordered_map>
#include <memory>
#include "core/ECS/ecs.hpp"
#include "core/ECS/Component_Array.hpp"

namespace Temporal::Core::ECS
{
    // manages all the component arrays when a component needs to be added or removed
    class Component_Manager
    {
    public:
        template <typename T>
        void Register_Component()
        {
            const char *type_name = typeid(T).name();

            // associate the new component type with a type name
            m_component_types.insert(std::make_pair(type_name, m_next_component_type));

            // creates a pointer to an array of the type of the component and associates with the type name of the component
            m_component_arrays.insert(std::make_pair(type_name, std::make_shared<Component_Array<T>>()));

            // increments the component type id
            m_next_component_type++;
        }

        // gets the component ID
        template <typename T>
        Component_Type Get_Component_Type()
        {
            const char *type_name = typeid(T).name();

            // used for creating component signatures
            return m_component_types[type_name];
        }

        // associates a component with an entity
        template<typename T>
        void Add_Component(Entity e, T component)
        {
            Get_Component_Array<T>()->Insert_Data(e, component);
        }

        // disassociate a component from an entity 
        template<typename T>
        void Remove_Component(Entity e)
        {
            Get_Component_Array<T>()->Remove_Data(e);
        }

        // gets the component of a giving type associated with an entity
        template<typename T>
        T& Get_Component(Entity e)
        {
            return Get_Component_Array<T>()->Get_Data(e);
        }

        void Entity_Destroyed_Event(Entity e)
        {
            for(auto const& pair : m_component_arrays)
            {
                auto const& component_array = pair.second;
                component_array->Entity_Destroyed(e);
            }
        }

    private:
        std::unordered_map<const char *, Component_Type> m_component_types{};

        // a map, where the key is a type name, and the value is a component array with all the components associated with entities 
        std::unordered_map<const char *, std::shared_ptr<IComponent_Array>> m_component_arrays{};
        Component_Type m_next_component_type{};


        // gets a component array from the map of components arrays, based on the type
        template <typename T>
        std::shared_ptr<Component_Array<T>> Get_Component_Array()
        {
            const char *type_name = typeid(T).name();
            // converts IComponentArray to Component_Array<T>
            return std::static_pointer_cast<Component_Array<T>>(m_component_arrays[type_name]);
        }
    };
}
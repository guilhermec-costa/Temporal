#pragma once
#include <unordered_map>
#include "core/ECS/ecs.hpp"

namespace Temporal::Core::ECS
{
    class IComponent_Array
    {
    public:
        virtual ~IComponent_Array() = default;
        virtual void Entity_Destroyed(Entity e) = 0;
    };

    // a packed array, in other words, there's no empty space between items. It is contiguous
    // it is a wrapper around a std::array, but with packed-like funcionallity
    // it is a array containing all the components of a giving type
    template <typename T>
    class Component_Array : public IComponent_Array
    {
    public:
        // associates a component with an entity
        void Insert_Data(Entity e, T component)
        {
            size_t new_idx = m_size;
            m_entity_to_idx_map[e] = new_idx;
            m_idx_to_entity_map[new_idx] = e;

            m_components_array[new_idx] = component;
            m_size++;
        }

        // disassociate a component from an entity
        void Remove_Data(Entity e)
        {
            // gets the index from the component array of the entity that will be removed
            size_t idx_of_removed_entity = m_entity_to_idx_map[e];
            size_t idx_of_last_element = m_size - 1;

            // this fills the components array at the index of the entity that will be removed,
            // with the data of the last component
            m_components_array[idx_of_removed_entity] = m_components_array[idx_of_last_element];

            // gets the entity associated with the last component
            Entity entity_of_last_element = m_idx_to_entity_map[idx_of_last_element];

            // updates the maps, to correspond to the new state of components arrays
            m_entity_to_idx_map[entity_of_last_element] = idx_of_removed_entity;
            m_idx_to_entity_map[idx_of_removed_entity] = entity_of_last_element;

            m_entity_to_idx_map.erase(e);
            m_idx_to_entity_map.erase(idx_of_last_element);
            m_size--;
        }

        // gets the component of a giving type associated with an entity
        T &Get_Data(Entity e)
        {
            return m_components_array[m_entity_to_idx_map[e]];
        }

        void Entity_Destroyed(Entity e) override
        {
            if (m_entity_to_idx_map.find(e) != m_entity_to_idx_map.end())
            {
                Remove_Data(e);
            }
        }

    private:
        // each array index represents an entity, and the value is the associated component
        std::array<T, MAX_ENTITIES> m_components_array;

        // map Entity->Array index
        std::unordered_map<Entity, size_t> m_entity_to_idx_map;

        // map Array index->Entity
        std::unordered_map<size_t, Entity> m_idx_to_entity_map;
        size_t m_size;
    };
}
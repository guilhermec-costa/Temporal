#pragma once
#include <set>
#include "core/ECS/ecs.hpp"

namespace Temporal::Core::ECS
{
    // a funcionallity that iterates upon entities with a certain component signature
    class System
    {
    public:
        // list of entities that the system will iterate upon
        std::set<Entity> m_entites;
    };
}
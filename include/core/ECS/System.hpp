#pragma once
#include <set>
#include <vector>
#include "core/ECS/ecs.hpp"

namespace Temporal::Core::ECS
{
    // a funcionallity that iterates upon entities with a certain component signature
    class System
    {
    public:
        // list of entities that the system will iterate upon
        std::vector<Entity> m_entites;
    };
}
#pragma once
#include "core/ECS/System.hpp"
#include "core/ECS/ECS_Orchestrator.hpp"
#include "core/ECS/components/Transform_Component.hpp"
#include <iostream>

using namespace Temporal::Core::ECS;

extern Temporal::Core::ECS::ECS_Orchestrator gECS_Orchestrator;

namespace Temporal::Core::ECS::Systems
{
    class Position_System : public System
    {
    public:
        void update()
        {
            for (auto const &entity : m_entites)
            {
                auto &transform = gECS_Orchestrator.Get_Component<Transform_Component>(entity);
                Vector2D current_position = transform.get_position();
                transform.set_position(current_position.add(Vector2D(1, 0)));
            }
        }
    };
}

using Position_System = Temporal::Core::ECS::Systems::Position_System;
#pragma once
#include "core/ECS/System.hpp"
#include "core/ECS/ECS_Orchestrator.hpp"
#include "core/ECS/components/Position_Component.hpp"
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
                auto &position = gECS_Orchestrator.Get_Component<Position_Component>(entity);
                position.set_x(position.x + 1);
                position.set_y(position.y + 1);
            }
        }
    };
}

using Position_System = Temporal::Core::ECS::Systems::Position_System;
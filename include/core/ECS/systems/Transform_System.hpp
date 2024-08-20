#pragma once
#include "core/ECS/System.hpp"
#include "core/ECS/ECS_Orchestrator.hpp"
#include "core/ECS/components/Transform_Component.hpp"
#include "core/ECS/components/Velocity_Component.hpp"
#include "core/ECS/components/Collider_Component.hpp"
#include <iostream>

using namespace Temporal::Core::ECS;

extern Temporal::Core::ECS::ECS_Orchestrator gECS_Orchestrator;

namespace Temporal::Core::ECS::Systems
{
    class Transform_System : public System
    {
    public:
        void update()
        {
            for (auto const &entity : m_entites)
            {
                auto &transform = gECS_Orchestrator.Get_Component<Transform_Component>(entity);
                auto &velocity = gECS_Orchestrator.Get_Component<Velocity_Component>(entity);
                auto &collider = gECS_Orchestrator.Get_Component<Collider_Component>(entity);
                transform.m_position += velocity.get_velocity();
                transform.m_position += velocity.get_velocity();
            }
        }
    };
}

using Transform_System = Temporal::Core::ECS::Systems::Transform_System;
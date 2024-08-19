#pragma once
#include "core/ECS/System.hpp"
#include "core/ECS/ECS_Orchestrator.hpp"
#include "core/ECS/components/Collider_Component.hpp"
#include "core/ECS/components/Transform_Component.hpp"
#include "core/ECS/components/Sprite_Component.hpp"
#include "core/ECS/components/Size_Component.hpp"
#include "game/Collision_Orchestrator.h"
#include <iostream>

using namespace Temporal::Core::ECS;

extern Temporal::Core::ECS::ECS_Orchestrator gECS_Orchestrator;

namespace Temporal::Core::ECS::Systems
{
    class Collider_System : public System
    {
    public:
        void update()
        {
            for (size_t i = 0; i < m_entites.size(); ++i)
            {
                Entity &entityA = m_entites[i];
                auto &collider_cp_A = gECS_Orchestrator.Get_Component<Collider_Component>(entityA);
                auto &transform_cp = gECS_Orchestrator.Get_Component<Transform_Component>(entityA);
                auto &sprite = gECS_Orchestrator.Get_Component<Sprite_Component>(entityA);

                Vector2D position = transform_cp.get_position();
                Vector2D scale = transform_cp.get_scale();

                collider_cp_A.set_coords(position.m_x, position.m_y);
                collider_cp_A.set_dimensions(sprite.m_dst_rect.w * scale.m_x, sprite.m_dst_rect.h * scale.m_y);

                for (size_t j = i + 1; j < m_entites.size(); ++j)
                {
                    Entity &entityB = m_entites[j];
                    auto &collider_cp_B = gECS_Orchestrator.Get_Component<Collider_Component>(entityB);
                    bool collided = Collision_Orchestrator::AABB(collider_cp_A.m_collider, collider_cp_B.m_collider);
                    if (collided)
                    {
                        std::cout << "Tag " << collider_cp_B.m_tag << " collided with " << collider_cp_A.m_tag << "\n";
                    }
                }
            }
        }
    };
}

using Collider_System = Temporal::Core::ECS::Systems::Collider_System;

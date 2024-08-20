#pragma once
#include <SDL2/SDL_render.h>
#include "game/Temporal_Game.h"
#include "core/ECS/ecs.hpp"
#include "core/ECS/ECS_Orchestrator.hpp"
#include "core/ECS/System.hpp"
#include "utils/Temporal_Texture_Manager.h"
#include "core/ECS/components/Sprite_Component.hpp"
#include "core/ECS/components/Collider_Component.hpp"

extern Temporal::Core::ECS::ECS_Orchestrator gECS_Orchestrator;

namespace Temporal::Core::ECS::Systems
{
    class Render_System : public System
    {
    public:
        void update(SDL_Renderer *renderer)
        {
            for (auto const &entity : m_entites)
            {
                auto &sprite = gECS_Orchestrator.Get_Component<Sprite_Component>(entity);
                auto &transform = gECS_Orchestrator.Get_Component<Transform_Component>(entity);
                auto &collider = gECS_Orchestrator.Get_Component<Collider_Component>(entity);

                int xpos = transform.m_position.m_x;
                int ypos = transform.m_position.m_y;
                sprite.set_position(xpos, ypos);

                Temporal_Texture_Manager::get().draw(
                    sprite.m_texture_path, sprite.m_src_rect, sprite.m_dst_rect, renderer);

                if (collider.m_outlined)
                {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                    collider.draw_outline(renderer);
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                }
            }
        }
    };
}

using Render_System = Temporal::Core::ECS::Systems::Render_System;
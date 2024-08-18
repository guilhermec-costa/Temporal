#pragma once
#include <SDL2/SDL_render.h>
#include "game/Temporal_Game.h"
#include "core/ECS/ecs.hpp"
#include "core/ECS/ECS_Orchestrator.hpp"
#include "core/ECS/System.hpp"
#include "utils/Temporal_Texture_Manager.h"
#include "core/ECS/components/Sprite_Component.hpp"

extern Temporal::Core::ECS::ECS_Orchestrator gECS_Orchestrator;

namespace Temporal::Core::ECS::Systems
{
    class Render_System : public System
    {
    public:
        void render(SDL_Renderer *renderer)
        {
            for (auto const &entity : m_entites)
            {
                auto &sprite = gECS_Orchestrator.Get_Component<Sprite_Component>(entity);
                auto &transform = gECS_Orchestrator.Get_Component<Transform_Component>(entity);
                sprite.m_dst_rect.x = transform.m_position.m_x;
                sprite.m_dst_rect.y = transform.m_position.m_y;
                Temporal_Texture_Manager::get().draw(
                    sprite.m_texture_path, sprite.m_src_rect, sprite.m_dst_rect, renderer);
            }
        }
    };
}

using Render_System = Temporal::Core::ECS::Systems::Render_System;
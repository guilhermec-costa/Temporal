#pragma once
#include <SDL2/SDL_render.h>
#include <string>
#include "core/ECS/ecs.hpp"

namespace Temporal::Core::ECS::Components
{
    struct Sprite_Component
    {
        float x, y;
        const char* m_texture_path;
        SDL_Rect m_src_rect, m_dst_rect;

        Sprite_Component(const char* path, const SDL_Rect& src_rect, const SDL_Rect& dst_rect) 
            : m_texture_path(path), m_src_rect(src_rect), m_dst_rect(dst_rect) {}
    };
}

using Sprite_Component = Temporal::Core::ECS::Components::Sprite_Component;
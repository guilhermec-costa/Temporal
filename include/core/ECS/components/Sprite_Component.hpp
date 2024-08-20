#pragma once
#include <SDL2/SDL_render.h>
#include <string>
#include "core/ECS/ecs.hpp"

namespace Temporal::Core::ECS::Components
{
    struct Sprite_Component
    {
        float x, y;
        const char *m_texture_path;
        Vector2D m_dimensions;
        SDL_Rect m_src_rect;
        SDL_Rect m_dst_rect;
        float m_angle = 0.0f;
        SDL_Point* m_center = nullptr;
        SDL_RendererFlip m_flip = SDL_FLIP_NONE;

        Sprite_Component(const char *path, const SDL_Rect &src_rect, const Vector2D &dim)
            : m_texture_path(path), m_dimensions(dim), m_src_rect(src_rect)
        {
            m_dst_rect.w = m_dimensions.m_x;
            m_dst_rect.h = m_dimensions.m_y;
        }

        void set_position(int x, int y)
        {
            m_dst_rect.x = x;
            m_dst_rect.y = y;
        }
    };
}

using Sprite_Component = Temporal::Core::ECS::Components::Sprite_Component;
#pragma once
#include <SDL2/SDL_rect.h>
#include <string>

namespace Temporal::Core::ECS::Components
{
    struct Collider_Component
    {
        SDL_Rect m_collider;
        const char *m_tag;
        bool m_outlined;
        bool is_colliding;

        Collider_Component(int w, int h, int x, int y, const char *tag)
            : m_collider{x, y, w, h}, m_tag(tag), m_outlined(false), is_colliding(false)
        {
        }

        void set_coords(int x, int y)
        {
            m_collider.x = x;
            m_collider.y = y;
        }

        void set_dimensions(int w, int h)
        {
            m_collider.w = w;
            m_collider.h = h;
        }
    };
}

using Collider_Component = Temporal::Core::ECS::Components::Collider_Component;
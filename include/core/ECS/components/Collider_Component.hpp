#pragma once
#include <SDL2/SDL_rect.h>

namespace Temporal::Core::ECS::Components
{
    struct Collider_Component
    {
        SDL_Rect m_collider;
        std::string m_tag;

        Collider_Component(int w, int h, int x, int y, const std::string& tag)
            : m_tag(tag)
        {
            m_collider.w = w;
            m_collider.h = h;
            m_collider.x = x;
            m_collider.y = y;
        }

        void set_coords(int x, int y) {
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
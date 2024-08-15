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
        int m_width, m_height;

        Sprite_Component(const char* path, int w, int h) : m_texture_path(path), m_width(w), m_height(h) {}

        float get_x() const { return x; }
        float get_y() const { return y; }
        void set_x(float _x) { x = _x; }
        void set_y(float _y) { y = _y; }
    };
}

using Sprite_Component = Temporal::Core::ECS::Components::Sprite_Component;
#pragma once

#include "core/ECS/components/Position_Component.hpp"
#include <SDL2/SDL_render.h>

namespace Temporal::Core::ECS::Components
{
    struct Sprite_Component : public Component
    {
        Sprite_Component(const std::string &texture_path, Position_Component &pos_cp)
            : m_texture_path(texture_path), m_position_component(pos_cp) {}
        std::string &get_texture_path() { return m_texture_path; }
        void set_texture_path(const std::string &_path) { m_texture_path = _path; }
        Position_Component &get_position_component() { return m_position_component; }

    private:
        Position_Component &m_position_component;
        std::string m_texture_path;
    };
}

using Sprite_Component = Temporal::Core::ECS::Components::Sprite_Component;
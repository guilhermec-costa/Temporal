#pragma once
#include "core/ECS/ecs.hpp"

namespace Temporal::Core::ECS::Components {
    struct Position_Component : public Component
    {
        float x, y;

        Position_Component(): x(0.0f), y(0.0f) {}
        Position_Component(float x, float y): x(x), y(y) {}

        void set_x(float _x) { x = _x; }
        void set_y(float _y) { y = _y; }
    };
}

using Position_Component = Temporal::Core::ECS::Components::Position_Component;
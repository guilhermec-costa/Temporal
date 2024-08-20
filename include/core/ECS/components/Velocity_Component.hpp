#pragma once
#include "core/math/Vector2D.h"

namespace Temporal::Core::ECS::Components
{
    struct Velocity_Component
    {
        Vector2D m_velocity;
        float speed;
        Velocity_Component(float x, float y) : m_velocity(x, y), speed(2.5) {}

        Vector2D get_velocity()
        {
            return m_velocity;
        }
        void set_velocity(const Vector2D &velocity)
        {
            m_velocity = velocity;
        }
    };
}

using Velocity_Component = Temporal::Core::ECS::Components::Velocity_Component;
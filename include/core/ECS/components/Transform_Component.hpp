#pragma once
#include "core/ECS/ecs.hpp"
#include "core/math/Vector2D.h";

namespace Temporal::Core::ECS::Components
{
    struct Transform_Component
    {
        Transform_Component()
            : m_position(0.0f, 0.0f), m_rotation(0.0f), m_scale(1.0f, 1.0f) {}
        Transform_Component(Vector2D position, float rotation, Vector2D scale)
            : m_position(position), m_rotation(rotation), m_scale(scale) {}

        Vector2D m_position;
        float m_rotation;
        Vector2D m_scale;

        Vector2D get_position() const { return m_position; }
        void set_position(Vector2D position) { m_position = position; }

        // float get_rotation() const { return m_rotation; }
        // void set_rotation(float rotation) { m_rotation = rotation; }

        Vector2D get_scale() const { return m_scale; }
        void set_scale(Vector2D scale) { m_scale = scale; }
    };
}

using Transform_Component = Temporal::Core::ECS::Components::Transform_Component;
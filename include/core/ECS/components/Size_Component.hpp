#pragma once
#include "core/math/Vector2D.h"

namespace Temporal::Core::ECS::Components {
    struct Size_Component 
    {
        Vector2D m_size;
        Size_Component(float x, float y): m_size(x, y) {}

        Vector2D get_size()
        {
            return m_size;
        }
        void set_size(const Vector2D& size)
        {
            m_size = size;
        }
    };
}

using Size_Component = Temporal::Core::ECS::Components::Size_Component;
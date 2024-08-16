#include "core/math/Vector2D.h"

namespace Temporal::Core::Math
{
    Vector2D::Vector2D() : m_x(0.0f), m_y(0.0f) {};

    Vector2D::Vector2D(float x, float y)
        : m_x(x), m_y(y) {}

    Vector2D &Vector2D::add(const Vector2D &v2)
    {
        this->m_x += v2.m_x;
        this->m_y += v2.m_y;
        return *this;
    };

    Vector2D &Vector2D::subtract(const Vector2D &v2)
    {
        this->m_x -= v2.m_x;
        this->m_y -= v2.m_y;
        return *this;
    }

    Vector2D &Vector2D::multiply(const Vector2D &v2)
    {
        this->m_x *= v2.m_x;
        this->m_y *= v2.m_y;
        return *this;
    }

    Vector2D &Vector2D::divide(const Vector2D &v2)
    {
        this->m_x /= v2.m_x;
        this->m_y /= v2.m_y;
        return *this;
    }

    Vector2D &Vector2D::operator+(const Vector2D &v2)
    {
        return this->add(v2);
    };

    Vector2D &Vector2D::operator-(const Vector2D &v2)
    {
        return this->subtract(v2);
    }

    Vector2D &Vector2D::operator*(const Vector2D &v2)
    {
        return this->multiply(v2);
    }

    Vector2D &Vector2D::operator/(const Vector2D &v2)
    {
        return this->divide(v2);
    }

    Vector2D &Vector2D::operator+=(const Vector2D &v2)
    {
        return this->add(v2);
    }

    Vector2D &Vector2D::operator-=(const Vector2D &v2)
    {
        return this->subtract(v2);
    }

    Vector2D &Vector2D::operator*=(const Vector2D &v2)
    {
        return this->multiply(v2);
    }

    Vector2D &Vector2D::operator/=(const Vector2D &v2)
    {
        return this->divide(v2);
    }
}
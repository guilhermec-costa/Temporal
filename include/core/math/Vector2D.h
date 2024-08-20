#pragma once
namespace Temporal::Core::Math
{
    struct Vector2D
    {
        Vector2D();
        Vector2D(float x, float y);

        Vector2D &add(const Vector2D &v2);
        Vector2D &subtract(const Vector2D &v2);
        Vector2D &multiply(const Vector2D &v2);
        Vector2D &divide(const Vector2D &v2);

        Vector2D &operator+(const Vector2D &v2);
        Vector2D &operator-(const Vector2D &v2);
        Vector2D &operator*(const Vector2D &v2);
        Vector2D &operator/(const Vector2D &v2);

        Vector2D &operator+=(const Vector2D &v2);
        Vector2D &operator-=(const Vector2D &v2);
        Vector2D &operator*=(const Vector2D &v2);
        Vector2D &operator/=(const Vector2D &v2);

        Vector2D &operator*(const int scale);

        float m_x, m_y;
    };
}

using Vector2D = Temporal::Core::Math::Vector2D;
#pragma once
namespace Temporal::Core
{

    class Vector2D
    {
    public:
        Vector2D(float x, float y) : m_x(x), m_y(y) {};
        float get_x() const { return m_x; }
        float get_y() const { return m_y; }

        void set_x(float x) { m_x = x; }
        void set_y(float y) { m_y = y; }

    private:
        float m_x, m_y;
    };
}
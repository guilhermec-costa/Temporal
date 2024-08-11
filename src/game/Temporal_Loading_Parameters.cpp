#include "game/Temporal_Loading_Parameters.h"

namespace Temporal::Game
{
    Temporal_Loading_Parameter::Temporal_Loading_Parameter(
        int x, int y,
        int width, int height,
        const std::string &texture_path)
        : m_x(x), m_y(y), m_width(width), m_height(height), m_texture_path(texture_path)
    {
    }

    int Temporal_Loading_Parameter::get_x() const { return m_x; }
    int Temporal_Loading_Parameter::get_y() const { return m_y; }
    int Temporal_Loading_Parameter::get_width() const { return m_width; }
    int Temporal_Loading_Parameter::get_height() const { return m_height; }
    std::string& Temporal_Loading_Parameter::get_texture_path() { return m_texture_path; }
}
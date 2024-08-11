#pragma once
#include <string>

namespace Temporal::Game
{
    class Temporal_Loading_Parameter
    {
    public:
        Temporal_Loading_Parameter(
            int x, int y,
            int width, int height,
            const std::string &texture_path);
        ~Temporal_Loading_Parameter() = default;

        int get_x() const;
        int get_y() const;
        int get_width() const;
        int get_height() const;
        std::string& get_texture_path();

    private:
        int m_x, m_y;
        int m_width, m_height;
        std::string m_texture_path;
    };
}

using Temporal_Loading_Parameter = Temporal::Game::Temporal_Loading_Parameter;
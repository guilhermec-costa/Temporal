#pragma once
#include "game/Temporal_Window.h"

namespace Temporal::Game
{
    class Temporal_SDL_Renderer
    {
    public:
        Temporal_SDL_Renderer(Temporal_SDL_Window &window);
        SDL_Renderer *get_renderer() const;
        void destroy();

    private:
        Temporal_SDL_Window &m_window;
        SDL_Renderer *m_renderer;
    };
};

using Temporal_SDL_Renderer = Temporal::Game::Temporal_SDL_Renderer;
#include <iostream>
#include "game/Temporal_Renderer.h"
#include "utils/Temporal_Logger.h"

namespace Temporal::Game {
    Temporal_SDL_Renderer::Temporal_SDL_Renderer(Temporal_SDL_Window& window)
        : m_window(window)
    {
        m_renderer = SDL_CreateRenderer(m_window.get_window(), -1, SDL_RENDERER_PRESENTVSYNC);
        if(m_renderer == NULL)
        {
            LOG_ERROR("Failed to create Temporal's Game Renderer");
        }
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
        LOG_INFO("Temporal's SDL Renderer created!")
    };

    void Temporal_SDL_Renderer::destroy()
    {
        SDL_DestroyRenderer(m_renderer);
    }

    SDL_Renderer* Temporal_SDL_Renderer::get_renderer() const { return m_renderer; }
}
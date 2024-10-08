#include "game/Temporal_Game.h"
#include "utils/Temporal_Logger.h"
#include "game/components/Temporal_Texture_Component.h"

namespace Temporal::Game
{
    Temporal_SDL_Window::Temporal_SDL_Window(const char *title, uint32_t w, uint32_t h)
        : m_width(w), m_heigth(h), m_title(title)
    {
        create();
    }

    void Temporal_SDL_Window::destroy()
    {
        SDL_DestroyWindow(m_window);
    }

    void Temporal_SDL_Window::create()
    {
        m_window = SDL_CreateWindow(m_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_heigth, SDL_WINDOW_SHOWN);
        if (!m_window)
        {
            LOG_ERROR("Failed to create Temporal's Game Window");
            return;
        }

        LOG_INFO("Temporal's SDL Window created!")
    }

    SDL_Window *Temporal_SDL_Window::get_window() const { return m_window; }
}
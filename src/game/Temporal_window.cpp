#include "game/Temporal_game.h"
#include "utils/Temporal_logger.h"

namespace Temporal::Game
{
    Game_Window::Game_Window(const char* title, uint32_t w, uint32_t h)
    {
        m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
        if(m_window)
        {
            LOG_ERROR("Failed to create Temporal's Game Window");
        }
    }
}
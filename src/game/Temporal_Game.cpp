#include "game/Temporal_game.h"
namespace Temporal::Game
{
    TemporalGame::TemporalGame(Temporal_SDL_Window& window)
        : m_main_window(window)
    {
        m_main_window.create();
    }

    TemporalGame::~TemporalGame()
    {
        m_main_window.destroy();
    }

    Temporal_SDL_Window& TemporalGame::get_window() const
    { 
        return m_main_window;
    }
}
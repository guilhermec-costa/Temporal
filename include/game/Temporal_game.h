#include "Temporal_window.h"

namespace Temporal::Game
{
    class TemporalGame
    {
    public:
        TemporalGame(Temporal_SDL_Window& window);
        ~TemporalGame();
        Temporal_SDL_Window& get_window() const;

    private:
        Temporal_SDL_Window& m_main_window;
    };
};



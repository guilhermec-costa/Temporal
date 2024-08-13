#pragma once
#include "game/Temporal_Window.h"
#include "game/Temporal_Renderer.h"

namespace Temporal::Game
{
    class TemporalGame
    {
    public:
        TemporalGame(Temporal_SDL_Window &window);
        ~TemporalGame();
        Temporal_SDL_Window &get_wrapper_window() const;
        SDL_Window *get_raw_window() const;
        uint32_t get_max_framerate() const;
        void set_max_framerate(uint32_t max_fr);
        bool executing() const;
        void process_inputs();
        void update();
        void render();
        void ends();
        static Temporal_SDL_Renderer* m_renderer;

    private:
        void setup_core_systems();

    private:
        Temporal_SDL_Window &m_main_window;
        bool m_is_executing;
        unsigned int m_max_framerate;
        static int IMG_system_flags; 
    };
};

using Temporal_Game = Temporal::Game::TemporalGame;
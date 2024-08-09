#pragma once
#include "Temporal_window.h"
#include "Temporal_renderer.h"

namespace Temporal::Game
{
    class TemporalGame
    {
    public:
        TemporalGame(Temporal_SDL_Window &window, Temporal_SDL_Renderer &renderer);
        ~TemporalGame();
        Temporal_SDL_Window &get_wrapper_window() const;
        Temporal_SDL_Renderer &get_wrapper_renderer() const;
        SDL_Renderer *get_raw_renderer() const;
        SDL_Window *get_raw_window() const;
        uint32_t get_max_framerate() const;
        void set_max_framerate(uint32_t max_fr);
        bool executing() const;
        void process_inputs();
        void update();
        void render();
        void ends();

    private:
        void setup_core_systems();

    private:
        Temporal_SDL_Window &m_main_window;
        Temporal_SDL_Renderer &m_main_renderer;
        bool m_is_executing;
        unsigned int m_max_framerate;
        static int IMG_system_flags; 
    };
};

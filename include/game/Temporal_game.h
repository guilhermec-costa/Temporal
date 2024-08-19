#pragma once
#include "game/Temporal_Window.h"
#include "game/Temporal_Renderer.h"
#include "core/ECS/systems/Transform_System.hpp"
#include "core/ECS/systems/Render_System.hpp"
#include "core/ECS/systems/Collider_System.hpp"

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
        void register_ECS_components();
        void register_ECS_systems();
        void set_ECS_component_signatures();
        void register_event_handlers();
        static Temporal_SDL_Renderer* m_renderer;

    private:
        void setup_core_systems();

    private:
        Temporal_SDL_Window &m_main_window;
        bool m_is_executing;
        unsigned int m_max_framerate;
        static int IMG_system_flags; 
        std::shared_ptr<Transform_System> m_position_system;
        std::shared_ptr<Render_System> m_render_system;
        std::shared_ptr<Collider_System> m_collider_system;
        static SDL_Event m_event;
    };
};

using Temporal_Game = Temporal::Game::TemporalGame;
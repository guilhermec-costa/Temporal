#include <iostream>
#include "SDL2/SDL_image.h"
#include "game/Temporal_Game.h"
#include "game/factories/Temporal_Game_Object_Factory.h"
#include "game/constants/Texture_Paths.hpp"
#include "utils/Temporal_Logger.h"
#include "utils/Temporal_Texture_Manager.h"
#include "game/entities/Temporal_Player.h"

Temporal_Player* player = nullptr;
int Temporal::Game::TemporalGame::IMG_system_flags = IMG_INIT_JPG | IMG_INIT_PNG;
using namespace Temporal::Resources;

namespace Temporal::Game
{
    namespace Factories = Temporal::Game::Factories;
    namespace Entities = Temporal::Game::Entities;

    TemporalGame::TemporalGame(Temporal_SDL_Window &window, Temporal_SDL_Renderer &renderer)
        : m_main_window(window), m_main_renderer(renderer), m_max_framerate(60)
    {
        setup_core_systems();
        if (m_is_executing)
            LOG_INFO("Temporal started!")

        Temporal_Texture_Manager::get().load(PLAYER_TEXTURE, renderer.get_renderer());
        Game_Object_Factory::get_instance().register_type("Player", new Player_Creator());
        player = dynamic_cast<Temporal_Player*>(Game_Object_Factory::get_instance().create("Player"));
        player->load(new Temporal_Loading_Parameter(30, 30, 64, 64, PLAYER_TEXTURE));
    }

    // must be done before game initialization
    void TemporalGame::setup_core_systems()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            LOG_ERROR("Failed to initialize SDL Video Subsystem")
            m_is_executing = false;
        }

        if((IMG_Init(IMG_system_flags) & IMG_system_flags) != IMG_system_flags)
        {
            LOG_ERROR("SDL2_image format not available");
            m_is_executing = false;
        }
        m_is_executing = true;
    }

    TemporalGame::~TemporalGame()
    {
        ends();
        LOG_INFO("Temporal has been closed");
    }

    Temporal_SDL_Window &TemporalGame::get_wrapper_window() const { return m_main_window; }
    Temporal_SDL_Renderer &TemporalGame::get_wrapper_renderer() const { return m_main_renderer; }
    SDL_Window *TemporalGame::get_raw_window() const { return m_main_window.get_window(); }
    SDL_Renderer *TemporalGame::get_raw_renderer() const { return m_main_renderer.get_renderer(); }
    bool TemporalGame::executing() const { return m_is_executing; }

    void TemporalGame::process_inputs()
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            m_is_executing = false;
            break;
        default:
            break;
        }
    }

    void TemporalGame::update()
    {
        player->update();
    }

    void TemporalGame::render()
    {
        SDL_Renderer *renderer = m_main_renderer.get_renderer();
        SDL_RenderClear(renderer);
        player->render(renderer);
        SDL_RenderPresent(renderer);
    }

    void TemporalGame::ends()
    {
        m_main_renderer.destroy();
        m_main_window.destroy();
        player->end();
        SDL_Quit();
    }

    uint32_t TemporalGame::get_max_framerate() const { return m_max_framerate; }
    void TemporalGame::set_max_framerate(uint32_t max_fr) { m_max_framerate = max_fr; }
}
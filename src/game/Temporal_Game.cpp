#include "game/Temporal_game.h"
#include "utils/Temporal_aliases.hpp"
#include "game/factories/Temporal_Game_Object_factory.h"
#include "game/entities/Temporal_Player.h"
#include "SDL2/SDL_image.h"
#include <iostream>

SDL_Rect src_rect, dst_rect;
SDL_Texture* player_texture;
Player* player = nullptr;
int TemporalGame::IMG_system_flags = IMG_INIT_JPG | IMG_INIT_PNG;

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

        Game_Object_Factory::get_instance().register_type("Player", new Player_Creator());
        Temporal_Texture_Manager::get().load(Temporal_Resources::PLAYER_TEXTURE, m_main_renderer.get_renderer());
        player = dynamic_cast<Player*>(Game_Object_Factory::get_instance().create("Player"));
        player->load(Temporal_Resources::PLAYER_TEXTURE);
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
        dst_rect.x = 10;
        dst_rect.y = 10;
        dst_rect.w = 128;
        dst_rect.h = 128;
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
        SDL_Quit();
    }

    uint32_t TemporalGame::get_max_framerate() const { return m_max_framerate; }
    void TemporalGame::set_max_framerate(uint32_t max_fr) { m_max_framerate = max_fr; }
}
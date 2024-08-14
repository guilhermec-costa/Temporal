#include <iostream>
#include "SDL2/SDL_image.h"
#include "game/Temporal_Game.h"
#include "game/factories/Temporal_Game_Object_Factory.h"
#include "game/constants/Texture_Paths.hpp"
#include "utils/Temporal_Logger.h"
#include "utils/Temporal_Texture_Manager.h"
#include "game/entities/Temporal_Player.h"
#include "game/map/Temporal_Tilemap.h"
#include "core/ECS/ECS_Orchestrator.hpp"
#include "core/ECS/components/Position_Component.hpp"
#include "core/ECS/components/Sprite_Component.hpp"

using namespace Temporal::Resources;
using namespace Temporal::Game::Map;
using namespace Temporal::Core::ECS;
ECS_Orchestrator gECS_Orchestrator;

int map_data[500] = {
    1, 1, 0, 0, 1, 0, 2, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0,
    1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1,
    0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 2, 1, 0, 1, 0, 1, 1, 0, 1, 2, 1, 0, 1, 1, 0,
    0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1,
    1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 2, 1, 0, 2, 0, 1, 0,
    1, 2, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 2, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0,
    1, 0, 1, 1, 2, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 2, 1, 0, 1, 0, 1, 1,
    0, 0, 1, 0, 0, 2, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0,
    1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1,
    1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0,
    1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 2, 0, 1, 0,
    1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 2, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1,
    0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0,
    0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 2, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1,
    1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0,
    1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1,
    1, 0, 0, 1, 0, 2, 0, 1, 0, 1, 1, 0, 2, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1,
    0, 2, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1,
    1, 0, 0, 1, 2, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0,
    1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 2, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0};

Entity player;
Temporal_Tilemap *map = nullptr;
int Temporal::Game::TemporalGame::IMG_system_flags = IMG_INIT_JPG | IMG_INIT_PNG;
Temporal_SDL_Renderer *Temporal::Game::TemporalGame::m_renderer = nullptr;

namespace Temporal::Game
{
    namespace Factories = Temporal::Game::Factories;
    namespace Entities = Temporal::Game::Entities;

    TemporalGame::TemporalGame(Temporal_SDL_Window &window)
        : m_main_window(window), m_max_framerate(60)
    {
        Temporal_SDL_Renderer *_renderer = new Temporal_SDL_Renderer(window);
        m_renderer = _renderer;
        setup_core_systems();
        if (m_is_executing)
            LOG_INFO("Temporal started!")

        gECS_Orchestrator.Init();
        register_ECS_components();
        register_ECS_systems();
        set_ECS_component_signatures();

        Temporal_Texture_Manager::get().load(PLAYER_TEXTURE, m_renderer->get_renderer());

        map = new Temporal_Tilemap(window.get_width(), window.get_height(), 32);
        map->load_map(map_data);

        player = gECS_Orchestrator.Create_Entity();
        gECS_Orchestrator.Add_Component<Position_Component>(player, Position_Component{1.0f, 2.0f});
        gECS_Orchestrator.Add_Component<Sprite_Component>(
            player, Sprite_Component{PLAYER_TEXTURE, gECS_Orchestrator.Get_Component<Position_Component>(player)});
    }

    // must be done before game initialization
    void TemporalGame::setup_core_systems()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            LOG_ERROR("Failed to initialize SDL Video Subsystem")
            m_is_executing = false;
        }

        if ((IMG_Init(IMG_system_flags) & IMG_system_flags) != IMG_system_flags)
        {
            LOG_ERROR("SDL2_image format not available");
            m_is_executing = false;
        }
        m_is_executing = true;
    }

    TemporalGame::~TemporalGame()
    {
        ends();
        delete map;
        LOG_INFO("Temporal has been closed");
    }

    Temporal_SDL_Window &TemporalGame::get_wrapper_window() const { return m_main_window; }
    SDL_Window *TemporalGame::get_raw_window() const { return m_main_window.get_window(); }
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
        // player->update();
    }

    void TemporalGame::render()
    {
        SDL_RenderClear(m_renderer->get_renderer());
        map->render_map();
        m_position_system->update();
        // player->render();
        SDL_RenderPresent(m_renderer->get_renderer());
    }

    void TemporalGame::ends()
    {
        m_renderer->destroy();
        m_main_window.destroy();
        gECS_Orchestrator.Destroy_Entity(player);
        // player->end();
        SDL_Quit();
    }

    void TemporalGame::register_ECS_components()
    {
        gECS_Orchestrator.Register_Component<Position_Component>();
        gECS_Orchestrator.Register_Component<Sprite_Component>();
    }

    void TemporalGame::register_ECS_systems()
    {
        m_position_system = gECS_Orchestrator.Register_System<Position_System>();
    }

    void TemporalGame::set_ECS_component_signatures()
    {
        Component_Signature signature;
        Component_Type position_component = gECS_Orchestrator.Get_Component_Type<Position_Component>();
        signature.set(position_component);
        gECS_Orchestrator.Set_System_Signature<Position_System>(signature);
    }

    uint32_t TemporalGame::get_max_framerate() const { return m_max_framerate; }
    void TemporalGame::set_max_framerate(uint32_t max_fr) { m_max_framerate = max_fr; }

}
#include <iostream>
#include <SDL2/SDL_image.h>
#include "game/Temporal_Game.h"
#include "game/constants/Texture_Paths.hpp"
#include "utils/Temporal_Logger.h"
#include "utils/Temporal_Texture_Manager.h"
#include "game/map/Temporal_Tilemap.h"
#include "core/ECS/ECS_Orchestrator.hpp"
#include "core/ECS/components/Transform_Component.hpp"
#include "core/ECS/components/Sprite_Component.hpp"
#include "game/events/Move_Event.h"
#include "game/events/event.h"
#include "game/events/Temporal_Event_Manager.h"

using namespace Temporal::Resources;
using namespace Temporal::Game::Map;
using namespace Temporal::Core::ECS;
using namespace Temporal::Game::Events;
ECS_Orchestrator gECS_Orchestrator;
Temporal_Event_Manager gEvent_manager;

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
SDL_Event Temporal_Game::m_event;

namespace Temporal::Game
{
    TemporalGame::TemporalGame(Temporal_SDL_Window &window)
        : m_main_window(window), m_max_framerate(60)
    {
        Temporal_SDL_Renderer *_renderer = new Temporal_SDL_Renderer(window);
        m_renderer = _renderer;

        this->setup_core_systems();
        if (m_is_executing)
            LOG_INFO("Temporal started!")

        gECS_Orchestrator.Init();
        this->register_ECS_components();
        this->register_ECS_systems();
        this->set_ECS_component_signatures();
        this->register_event_handlers();

        Temporal_Texture_Manager::get().load(PLAYER_TEXTURE, m_renderer->get_renderer());
        Temporal_Texture_Manager::get().load(BLOCKS, m_renderer->get_renderer());

        map = new Temporal_Tilemap(window.get_width(), window.get_height(), 32);
        map->load_map(map_data);

        player = gECS_Orchestrator.Create_Entity();
        gECS_Orchestrator.Add_Component(player,
                                        Transform_Component{
                                            Vector2D(100, 100),
                                            0.0f,
                                            Vector2D{1, 1}});

        gECS_Orchestrator.Add_Component(player,
                                        Sprite_Component{
                                            PLAYER_TEXTURE,
                                            SDL_Rect{0, 0, 32, 32},
                                            SDL_Rect{
                                                (int)gECS_Orchestrator.Get_Component<Transform_Component>(player).get_position().m_x,
                                                (int)gECS_Orchestrator.Get_Component<Transform_Component>(player).get_position().m_y,
                                                64, 64}});
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
        SDL_PollEvent(&m_event);
        switch (m_event.type)
        {
        case SDL_QUIT:
            m_is_executing = false;
            break;

        case SDL_KEYDOWN:
        {
            switch (m_event.key.keysym.sym)
            {
            case SDLK_d:
                Move_Event* event = new Move_Event(player, -3.0f, 0.0f);
                gEvent_manager.publish(event);
                break;
            }
            break;
        }
        default:
            break;
        }
        gEvent_manager.react();
    }

    void TemporalGame::update()
    {
        m_position_system->update();
    }

    void TemporalGame::render()
    {
        SDL_RenderClear(m_renderer->get_renderer());
        // map->render_map();
        m_render_system->render(m_renderer->get_renderer());
        SDL_RenderPresent(m_renderer->get_renderer());
    }

    void TemporalGame::ends()
    {
        m_renderer->destroy();
        m_main_window.destroy();
        // player->end();
        SDL_Quit();
    }

    void TemporalGame::register_ECS_components()
    {
        gECS_Orchestrator.Register_Component<Transform_Component>();
        gECS_Orchestrator.Register_Component<Sprite_Component>();
    }

    void TemporalGame::register_ECS_systems()
    {
        m_position_system = gECS_Orchestrator.Register_System<Position_System>();
        m_render_system = gECS_Orchestrator.Register_System<Render_System>();
    }

    void TemporalGame::set_ECS_component_signatures()
    {
        Component_Signature position_system_signature;
        Component_Type position_component = gECS_Orchestrator.Get_Component_Type<Transform_Component>();
        position_system_signature.set(position_component);
        gECS_Orchestrator.Set_System_Signature<Position_System>(position_system_signature);

        Component_Signature render_system_signature;
        Component_Type sprite_component = gECS_Orchestrator.Get_Component_Type<Sprite_Component>();
        render_system_signature.set(position_component);
        render_system_signature.set(sprite_component);
        gECS_Orchestrator.Set_System_Signature<Render_System>(render_system_signature);
    }

    void Temporal_Game::register_event_handlers()
    {
        auto *handler = new Move_Event_Handler();
        gEvent_manager.register_handler(Event_Type::Move, handler);
    }

    uint32_t TemporalGame::get_max_framerate() const { return m_max_framerate; }
    void TemporalGame::set_max_framerate(uint32_t max_fr) { m_max_framerate = max_fr; }

}
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
#include "core/ECS/components/Velocity_Component.hpp"
#include "core/ECS/components/Collider_Component.hpp"
#include "game/events/Move_Event.h"
#include "game/events/event.h"
#include "game/events/Temporal_Event_Manager.h"
#include "game/Temporal_Game.h"

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
Entity block;
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
        Temporal_Texture_Manager::get().load(WOOD, m_renderer->get_renderer());

        map = new Temporal_Tilemap(window.get_width(), window.get_height(), 32);
        map->load_map(map_data);

        player = gECS_Orchestrator.Create_Entity("player");
        gECS_Orchestrator.Add_Component<Transform_Component>(player, {Vector2D(100, 100), 0.0f, Vector2D(1, 1)});
        gECS_Orchestrator.Add_Component<Sprite_Component>(player, {PLAYER_TEXTURE, SDL_Rect{0, 0, 32, 32}, Vector2D(64, 64)});
        gECS_Orchestrator.Add_Component<Velocity_Component>(player, {0, 0});
        gECS_Orchestrator.Add_Component<Collider_Component>(player, {64, 64, 100, 100, gECS_Orchestrator.Get_Entity_Name(player)});
        gECS_Orchestrator.Get_Component<Collider_Component>(player).m_outlined = true;

        block = gECS_Orchestrator.Create_Entity("block");
        gECS_Orchestrator.Add_Component<Transform_Component>(block, {Vector2D(300, 100), 0.0f, Vector2D(1, 1)});
        gECS_Orchestrator.Add_Component<Sprite_Component>(block, {BLOCKS, SDL_Rect{35, 1, 16, 16}, Vector2D(64, 64)});
        gECS_Orchestrator.Add_Component<Velocity_Component>(block, {0, 0});
        gECS_Orchestrator.Add_Component<Collider_Component>(block, {64, 64, 300, 100, gECS_Orchestrator.Get_Entity_Name(block)});
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

    Temporal_SDL_Window &TemporalGame::get_wrapper_window() const
    {
        return m_main_window;
    }

    SDL_Window *TemporalGame::get_raw_window() const
    {
        return m_main_window.get_window();
    }

    bool TemporalGame::executing() const
    {
        return m_is_executing;
    }

    void TemporalGame::update()
    {
        m_position_system->update();
        m_collider_system->update();
    }

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
            case SDLK_ESCAPE:
            {
                if (m_is_paused)
                {
                    std::cout << "game unpaused" << "\n";
                    m_is_paused = false;
                }
                else
                {
                    std::cout << "game paused" << "\n";
                    m_is_paused = true;
                }
                break;
            }
            case SDLK_a:
            {
                std::unique_ptr<Event> event = std::make_unique<Move_Event>(player, Move_Event_Type::Move_LEFT);
                gEvent_manager.publish(event);
                break;
            }
            case SDLK_w:
            {
                std::unique_ptr<Event> event = std::make_unique<Move_Event>(player, Move_Event_Type::Move_UP);
                gEvent_manager.publish(event);
                break;
            }
            case SDLK_s:
            {
                std::unique_ptr<Event> event = std::make_unique<Move_Event>(player, Move_Event_Type::Move_DOWN);
                gEvent_manager.publish(event);
                break;
            }
            case SDLK_d:
            {
                std::unique_ptr<Event> event = std::make_unique<Move_Event>(player, Move_Event_Type::Move_RIGHT);
                gEvent_manager.publish(event);
                break;
            }
            }
            break;
        }
        case SDL_KEYUP:
        {
            switch (m_event.key.keysym.sym)
            {
            case SDLK_a:
            {
                std::unique_ptr<Event> event = std::make_unique<Move_Event>(player, Move_Event_Type::Stop_LEFT);
                gEvent_manager.publish(event);
                break;
            }
            case SDLK_w:
            {
                std::unique_ptr<Event> event = std::make_unique<Move_Event>(player, Move_Event_Type::Stop_UP);
                gEvent_manager.publish(event);
                break;
            }
            case SDLK_s:
            {
                std::unique_ptr<Event> event = std::make_unique<Move_Event>(player, Move_Event_Type::Stop_DOWN);
                gEvent_manager.publish(event);
                break;
            }
            case SDLK_d:
            {
                std::unique_ptr<Event> event = std::make_unique<Move_Event>(player, Move_Event_Type::Stop_RIGHT);
                gEvent_manager.publish(event);
                break;
            }
            }
            break;
        }
        default:
            break;
        }
        gEvent_manager.react();
    }

    void TemporalGame::render()
    {
        SDL_RenderClear(m_renderer->get_renderer());
        map->render_map();
        m_render_system->update(m_renderer->get_renderer());
        SDL_RenderPresent(m_renderer->get_renderer());
    }

    void TemporalGame::ends()
    {
        m_renderer->destroy();
        m_main_window.destroy();
        SDL_Quit();
    }

    void TemporalGame::register_ECS_components()
    {
        gECS_Orchestrator.Register_Component<Transform_Component>();
        gECS_Orchestrator.Register_Component<Sprite_Component>();
        gECS_Orchestrator.Register_Component<Velocity_Component>();
        gECS_Orchestrator.Register_Component<Collider_Component>();
    }

    void TemporalGame::register_ECS_systems()
    {
        m_collider_system = gECS_Orchestrator.Register_System<Collider_System>();
        m_position_system = gECS_Orchestrator.Register_System<Transform_System>();
        m_render_system = gECS_Orchestrator.Register_System<Render_System>();
    }

    void TemporalGame::set_ECS_component_signatures()
    {
        Component_Type transform_component = gECS_Orchestrator.Get_Component_Type<Transform_Component>();
        Component_Type velocity_component = gECS_Orchestrator.Get_Component_Type<Velocity_Component>();
        Component_Type sprite_component = gECS_Orchestrator.Get_Component_Type<Sprite_Component>();
        Component_Type collider_component = gECS_Orchestrator.Get_Component_Type<Collider_Component>();

        Component_Signature transform_system_signature;
        transform_system_signature.set(transform_component);
        transform_system_signature.set(velocity_component);
        transform_system_signature.set(collider_component);
        gECS_Orchestrator.Set_System_Signature<Transform_System>(transform_system_signature);

        Component_Signature collider_system_signature;
        collider_system_signature.set(transform_component);
        collider_system_signature.set(sprite_component);
        collider_system_signature.set(velocity_component);
        collider_system_signature.set(collider_component);
        gECS_Orchestrator.Set_System_Signature<Collider_System>(collider_system_signature);

        Component_Signature render_system_signature;
        render_system_signature.set(transform_component);
        render_system_signature.set(sprite_component);
        render_system_signature.set(collider_component);
        gECS_Orchestrator.Set_System_Signature<Render_System>(render_system_signature);
    }

    void TemporalGame::register_event_handlers()
    {
        gEvent_manager.register_subscribe<Move_Event>(new Move_Event_Subscriber());
    }

    uint32_t TemporalGame::get_max_framerate() const
    {
        return m_max_framerate;
    }
    void TemporalGame::set_max_framerate(uint32_t max_fr)
    {
        m_max_framerate = max_fr;
    }
}
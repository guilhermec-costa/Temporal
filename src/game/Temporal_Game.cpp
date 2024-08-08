#include "game/Temporal_game.h"
#include "utils/Temporal_logger.h"
#include "SDL2/SDL_image.h"

SDL_Rect src_rect, dst_rect;

SDL_Texture* player_texture;
namespace Temporal::Game
{
    TemporalGame::TemporalGame(Temporal_SDL_Window &window, Temporal_SDL_Renderer &renderer)
        : m_main_window(window), m_main_renderer(renderer), m_max_framerate(60)
    {
        setup_core_systems();
        if (m_is_executing)
            LOG_INFO("Temporal started!")
        SDL_Surface* sfc = IMG_Load("res\\gfx\\player_sprite.png");
        player_texture = SDL_CreateTextureFromSurface(renderer.get_renderer(), sfc);
        SDL_FreeSurface(sfc);
    }

    // must be done before game initialization
    void TemporalGame::setup_core_systems()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            LOG_ERROR("Failed to initialize SDL Video Subsystem\n")
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
        src_rect.w = 32;
        src_rect.h = 32;

        dst_rect.x = 10;
        dst_rect.y = 10;
        dst_rect.w = 32;
        dst_rect.h = 32;
    }

    void TemporalGame::render()
    {
        SDL_Renderer *renderer = m_main_renderer.get_renderer();
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, player_texture, &src_rect, &dst_rect);
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
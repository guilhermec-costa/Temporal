#include <iostream>
#include <SDL2/SDL.h>
#include "profiling/metrics.hpp"
#include <utils/Temporal_logger.h>
#include "game/Temporal_window.h"
#include "game/Temporal_game.h"

#undef main SDL_main

int main()
{
    using Logger = Temporal::Utils::Logger;
    using Game = Temporal::Game::TemporalGame;
    using Temporal_SDL_Window = Temporal::Game::Temporal_SDL_Window;
    Logger::get().set_log_level(loglvls::DEBUG);
    LOG_INFO("Game started!");
    Temporal_SDL_Window window("Temporal", 800, 600);
    Game game(window);
    using time_casts = Profiling::Time_Casting_Types;
    Profiling::Timer<time_casts::Milliseconds> timer("main");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        std::cout << "failed to initialize sdl video subsystem\n";
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window.get_window(), -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    return 0;
}
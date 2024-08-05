#include <iostream>
#include <SDL2/SDL.h>
#include "profiling/metrics.hpp"
#include <utils/Temporal_logger.h>
#undef main SDL_main

using Logger = Temporal::Utils::Logger;
int main()
{
    Logger::get().set_log_level(loglvls::DEBUG);
    LOG_INFO("Game started!");
    using time_casts = Profiling::Time_Casting_Types;
    Profiling::Timer<time_casts::Milliseconds> timer("main");
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        std::cout << "failed to initialize sdl video subsystem\n";
    }

    SDL_Window* window = SDL_CreateWindow("RPG2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    return 0;
}
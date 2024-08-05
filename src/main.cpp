#include <iostream>
#include <SDL2/SDL.h>
#include "profiling/metrics.h"
#undef main 

int main()
{
    using time_casts = Profiling::Time_Casting_Types;
    Profiling::Timer<time_casts::Milliseconds> timer("main");
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER ) != 0)
    {
        std::cout << "failed to initialize sdl video subsystem\n";
    }
    return 0;
}
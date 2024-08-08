#include <iostream>
#include <SDL2/SDL.h>
#include "profiling/metrics.hpp"
#include "utils/Temporal_aliases.hpp"
#include <SDL2/SDL_image.h>

#undef main

void *operator new(size_t size)
{
    std::cout << "allocated " << size << "\n";
    return malloc(size);
}

int main()
{
    Logger::get().set_log_level(loglvls::DEBUG);
    using time_casts = Profiling::Time_Casting_Types;


#ifdef DEBUG_ENABLED
    Profiling::Timer<time_casts::Milliseconds> timer("main");
#endif

    Temporal_SDL_Window window("Temporal", 800, 600);
    Temporal_SDL_Renderer renderer(window);
    TemporalGame temporalGame(window, renderer);

    while (temporalGame.executing())
    {
        temporalGame.process_inputs();
        temporalGame.render();
    }

    temporalGame.ends();
    return 0;
}
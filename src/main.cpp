#include <iostream>
#include <SDL2/SDL.h>
#include "profiling/timer.hpp"
#include "utils/Temporal_aliases.hpp"
#include <SDL2/SDL_image.h>
#include "profiling/memory_tracker.hpp"

#undef main

int main()
{
    Logger::get().set_log_level(loglvls::DEBUG);

    using time_casts = Profiling::Time_Casting_Types;

    Profiling::Timer<time_casts::Milliseconds> timer("main");
    Temporal_SDL_Window window("Temporal", 800, 600);
    Temporal_SDL_Renderer renderer(window);
    Temporal_Asset_Manager::get().load_asset(Temporal_Resources::PLAYER_TEXTURE);
    Temporal_Asset_Manager::get().load_asset(Temporal_Resources::PLAYER_SPRITE);

    TemporalGame temporalGame(window, renderer);


    //load_textures();
    temporalGame.set_max_framerate(120);


    const unsigned int MS_PER_FRAME = 1000 / temporalGame.get_max_framerate();

    uint32_t frame_previous_time = SDL_GetTicks();
    double lag = 0.0;
    while (temporalGame.executing())
    {
        uint32_t frame_start_time = SDL_GetTicks();
        uint32_t elapsed = frame_start_time - frame_previous_time;
        frame_previous_time = frame_start_time;
        lag += elapsed;

        temporalGame.process_inputs();

        while(lag >= MS_PER_FRAME)
        {
            temporalGame.update();
            lag -= MS_PER_FRAME;
        }

        temporalGame.render();
    }

    temporalGame.ends();
    //Memory_Tracker::get().report();
    return 0;
}
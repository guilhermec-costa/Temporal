#include <iostream>
#include <SDL2/SDL.h>
#include "profiling/timer.hpp"
#include "utils/Temporal_aliases.hpp"
#include <SDL2/SDL_image.h>
#include "profiling/memory_tracker.hpp"

#undef main

// Implementations of the global new/delete operators
void *operator new(size_t _s, const char *_f, int _l)
{
    return Memory_Tracker::get().alloc(_s, _f, _l);
}

void *operator new[](size_t size, const char *file, int line)
{
    return Memory_Tracker::get().alloc(size, file, line);
}
#define new new(__FILE__, __LINE__)

void operator delete(void *ptr) noexcept
{
    Memory_Tracker::get()._free(ptr);
}

void operator delete[](void *ptr) noexcept
{
    Memory_Tracker::get()._free(ptr);
}

int main()
{
    int* x = new int;
    Logger::get().set_log_level(loglvls::DEBUG);
    using time_casts = Profiling::Time_Casting_Types;

    Profiling::Timer<time_casts::Milliseconds> timer("main");

    Temporal_SDL_Window window("Temporal", 800, 600);
    Temporal_SDL_Renderer renderer(window);
    TemporalGame temporalGame(window, renderer);

    while (temporalGame.executing())
    {
        temporalGame.process_inputs();
        temporalGame.render();
    }

    temporalGame.ends();
    Memory_Tracker::get().report();
    return 0;
}
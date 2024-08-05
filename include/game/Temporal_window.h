#pragma once
#include <SDL2/SDL.h>

namespace Temporal::Game
{
    class Game_Window 
    {
        public:
            Game_Window(const char* title, uint32_t w, uint32_t h);
        private:    
            SDL_Window* m_window;
    };
}
#pragma once
#include "Temporal_IGame_object.h"

namespace Temporal::Game {
    class Temporal_SDL_Game_Object: public Temporal_IGame_Object
    {
        public:
            Temporal_SDL_Game_Object();
            virtual void render();
            virtual void update();
            virtual void end(); 
    };
}
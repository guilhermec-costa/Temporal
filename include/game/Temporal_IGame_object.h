#pragma once
#include "SDL2/SDL_render.h"
#include <string>

namespace Temporal::Game
{
    class Temporal_IGame_Object
    {
    public:
        virtual void render(SDL_Renderer* renderer) = 0;
        virtual void update() = 0;
        virtual void end() = 0;
        virtual void load(const std::string&) = 0;

    protected:
        Temporal_IGame_Object() = default;
        virtual ~Temporal_IGame_Object() = default;
    };
}

typedef Temporal::Game::Temporal_IGame_Object Game_Object;
#pragma once
#include <string>
#include "SDL2/SDL_render.h"

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

using Temporal_Game_Object = Temporal::Game::Temporal_IGame_Object;
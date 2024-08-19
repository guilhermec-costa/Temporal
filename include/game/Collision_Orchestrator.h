#pragma once
#include <SDL2/SDL_rect.h>

namespace Temporal::Game
{
    class Collision_Orchestrator
    {
    public:
        static bool AABB(const SDL_Rect &_rA, const SDL_Rect &_rB);
    };
}

using Collision_Orchestrator = Temporal::Game::Collision_Orchestrator;
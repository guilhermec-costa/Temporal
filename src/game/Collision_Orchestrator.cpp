#include "game/Collision_Orchestrator.h"
#include <SDL2/SDL.h>

namespace Temporal::Game
{
    bool Collision_Orchestrator::AABB(const SDL_Rect &_rA, const SDL_Rect &_rB)
    {
        if (
            _rA.x + _rA.w >= _rB.x &&
            _rB.x + _rB.w >= _rA.x &&
            _rA.y + _rA.h >= _rB.y &&
            _rB.y + _rB.h >= _rA.y)
            return true;

        return false;
    };
}
#include "game/entities/Temporal_Player.h"
#include "SDL2/SDL_render.h"
namespace Temporal::Game::Entities
{
    Temporal::Game::Entities::Player::Player::Player(): Temporal_SDL_Game_Object()
    {
    }

    void Temporal::Game::Entities::Player::render(SDL_Renderer* renderer)
    {
        Temporal_SDL_Game_Object::render(renderer);
    }

    void Temporal::Game::Entities::Player::update()
    {
    }

    void Temporal::Game::Entities::Player::end()
    {
    }

    void Temporal::Game::Entities::Player::load(Temporal_Loading_Parameter* params)
    {
        Temporal_SDL_Game_Object::load(params);
    }
}
#include "game/entities/Temporal_Player.h"
#include "SDL2/SDL_render.h"
namespace Temporal::Game::Entities
{
    Temporal::Game::Entities::Player::Player::Player(): Temporal_SDL_Game_Object()
    {
    }

    void Temporal::Game::Entities::Player::render()
    {
        Temporal_SDL_Game_Object::render();
    }

    void Temporal::Game::Entities::Player::update()
    {
        // m_position.set_x(m_position.get_x() + 1);
        // m_position.set_y(m_position.get_x() + 1);
    }

    void Temporal::Game::Entities::Player::end()
    {
    }

    void Temporal::Game::Entities::Player::load(Temporal_Loading_Parameter* params)
    {
        Temporal_SDL_Game_Object::load(params);
    }
}
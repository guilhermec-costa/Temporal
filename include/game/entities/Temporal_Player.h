#pragma once
#include "Temporal_SDL_Game_object.h"
#include "game/factories/Temporal_Game_Object_factory.h"

namespace Factories = Temporal::Game::Factories;
namespace Temporal::Game::Entities
{
    class Player : public Temporal_SDL_Game_Object
    {
        public:
            Player();
            virtual void render();
            virtual void update();
            virtual void end();
    };

    class Player_Creator: public Factories::Base_Creator
    {
        Player* create_game_object() const override
        {
            return new Player();
        }
    };
}
#pragma once
#include "game/Temporal_SDL_Game_Object.h"
#include "game/factories/Temporal_Game_Object_Factory.h"

namespace Factories = Temporal::Game::Factories;
namespace Temporal::Game::Entities
{
    class Player : public Temporal_SDL_Game_Object
    {
        public:
            Player();
            virtual void render(SDL_Renderer* renderer);
            virtual void update();
            virtual void end();
            void load(const std::string& texture_path);
    };

    class Player_Creator: public Factories::Temporal_Base_Creator
    {
        Temporal_IGame_Object* create_game_object() const override
        {
            return new Player();
        }
    };
}

using Player_Creator = Temporal::Game::Entities::Player_Creator;
using Temporal_Player = Temporal::Game::Entities::Player;
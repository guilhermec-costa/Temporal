#pragma once
#include "game/Temporal_SDL_Game_object.h"
#include "game/factories/Temporal_Game_Object_factory.h"

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

typedef Temporal::Game::Entities::Player_Creator Player_Creator;
typedef Temporal::Game::Entities::Player Player;
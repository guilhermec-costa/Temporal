#pragma once
#include "game/Temporal_IGame_object.h"
#include <unordered_map>
#include <string>

namespace Temporal::Game::Factories
{
    class Temporal_Base_Creator
    {
    public:
        virtual Temporal_IGame_Object *create_game_object() const = 0;
        virtual ~Temporal_Base_Creator() = default;
    };


    class Temporal_Game_Object_Factory
    {
    public:
        static Temporal_Game_Object_Factory &get_instance()
        {
            static Temporal_Game_Object_Factory instance;
            return instance;
        }

        bool register_type(const std::string &typeId, Temporal_Base_Creator* bc);
        Game_Object *create(const std::string &typeId);

    private:
        Temporal_Game_Object_Factory() = default;
        Temporal_Game_Object_Factory(const Temporal_Game_Object_Factory &cpy) = delete;
        ~Temporal_Game_Object_Factory();
        Temporal_Game_Object_Factory &operator=(const Temporal_Game_Object_Factory &cpy) = delete;
        std::unordered_map<std::string, Temporal_Base_Creator*> m_base_creators;
    };

}

typedef Temporal::Game::Factories::Temporal_Game_Object_Factory Game_Object_Factory;
typedef Temporal::Game::Factories::Temporal_Base_Creator Object_Base_Creator;
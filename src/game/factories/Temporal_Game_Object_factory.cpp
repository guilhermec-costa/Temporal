#include "game/factories/Temporal_Game_Object_factory.h"

namespace Temporal::Game::Factories
{
    Temporal_IGame_Object* Temporal_Game_Object_Factory::create(const std::string& typeId)
    {
        auto it = m_base_creators.find(typeId);
        if (it == m_base_creators.end())
        {
            return nullptr;
        }

        Base_Creator *bc = it->second;
        return bc->create_game_object();
    };

    bool Temporal_Game_Object_Factory::register_type(const std::string& typeId)
    {
    }
}
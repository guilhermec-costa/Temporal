#include "game/factories/Temporal_Game_Object_Factory.h"

namespace Temporal::Game::Factories
{
    Temporal_Game_Object* Temporal_Game_Object_Factory::create(const std::string& typeId)
    {
        auto it = m_base_creators.find(typeId);
        if (it == m_base_creators.end())
        {
            return nullptr;
        }

        Object_Base_Creator *bc = it->second;
        return bc->create_game_object();
    };

    bool Temporal_Game_Object_Factory::register_type(const std::string& typeId, Temporal_Base_Creator* bc)
    {
        auto it = m_base_creators.find(typeId);
        if(it != m_base_creators.end())
        {
            delete bc;
            return false;
        }

        m_base_creators[typeId] = bc;
        return true;
    }

    Temporal_Game_Object_Factory::~Temporal_Game_Object_Factory()
    {
        for(auto it=m_base_creators.begin(); it != m_base_creators.end(); it++)
        {
            delete it->second;
        }
    }
}
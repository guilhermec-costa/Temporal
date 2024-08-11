#include <string>
#include "game/Temporal_SDL_Game_Object.h"
#include "utils/Temporal_Texture_Manager.h"
#include "game/Temporal_Game.h"

namespace Temporal::Game {
    using Texture_Manager = Temporal::Utils::Temporal_Texture_Manager;
    Temporal_SDL_Game_Object::Temporal_SDL_Game_Object(): Temporal_IGame_Object(),
         m_position(0, 0)
    {
    }

    void Temporal_SDL_Game_Object::render()
    {
        Texture_Manager::get().draw(
            m_texture_path, 
            static_cast<int>(m_position.get_x()), 
            static_cast<int>(m_position.get_y()), 
            m_width, m_height, Temporal_Game::m_renderer->get_renderer()
        );
    }

    void Temporal_SDL_Game_Object::update()
    {
    }

    void Temporal_SDL_Game_Object::end()
    {
    }

    void Temporal_SDL_Game_Object::load(Temporal_Loading_Parameter* params)
    {
        m_texture_path = params->get_texture_path();
        m_position = Vector2D(params->get_x(), params->get_y());
        m_width = params->get_width();
        m_height = params->get_height();
        m_params = params;
    }

    Temporal_SDL_Game_Object::~Temporal_SDL_Game_Object()
    {
        delete m_params;
    }
}
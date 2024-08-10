#include "game/Temporal_SDL_Game_object.h"
#include "utils/Temporal_Texture_manager.h"
namespace Temporal::Game {
    using Texture_Manager = Temporal::Utils::Temporal_Texture_Manager;
    Temporal_SDL_Game_Object::Temporal_SDL_Game_Object(): Temporal_IGame_Object(),
         m_position(0, 0)
    {
        m_width = 32;
        m_height = 32;
    }

    void Temporal_SDL_Game_Object::render(SDL_Renderer* renderer)
    {
        Texture_Manager::get().draw(
            m_texture_path, 
            static_cast<int>(m_position.get_x()), 
            static_cast<int>(m_position.get_y()), 
            m_width, m_height, renderer
        );
    }

    void Temporal_SDL_Game_Object::update()
    {
    }

    void Temporal_SDL_Game_Object::end()
    {
    }

    void Temporal_SDL_Game_Object::load(const std::string& texture_path)
    {
        m_texture_path = texture_path;
    }
}
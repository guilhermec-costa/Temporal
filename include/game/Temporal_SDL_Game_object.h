#pragma once
#include <string>
#include "game/Temporal_IGame_Object.h"
#include "game/Temporal_Loading_Parameters.h"
#include "core/Vector2D.h"

namespace Temporal::Game
{
    class Temporal_SDL_Game_Object : public Temporal_IGame_Object
    {
        using Vector2D = Temporal::Core::Vector2D;

    public:
        Temporal_SDL_Game_Object();
        ~Temporal_SDL_Game_Object();
        virtual void render(SDL_Renderer* renderer);
        virtual void update();
        virtual void end();
        void load(Temporal_Loading_Parameter* params);
        Vector2D& get_position() { return m_position; }
        int get_width() const { return m_width; }
        int get_height() const { return m_height; }

    protected:
        Vector2D m_position;
        int m_width, m_height;
        std::string m_texture_path;
        Temporal_Loading_Parameter* m_params;
    };
}

using Temporal_SDL_Game_Object = Temporal::Game::Temporal_SDL_Game_Object;
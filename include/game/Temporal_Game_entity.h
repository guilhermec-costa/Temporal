#pragma once
#include "Temporal_game.h"

namespace Temporal::Game
{
    class Temporal_Game_Entity
    {
    public:
        Temporal_Game_Entity(SDL_Texture *entity_texture, SDL_Renderer *entity_renderer);
        ~Temporal_Game_Entity();
        void update();
        void render();

    private:
        struct
        {
            int x;
            int y;
        } coords;

        SDL_Texture* m_entity_texture;
        SDL_Renderer* m_entity_renderer;
        SDL_Rect m_src_rect, m_dst_rect;
    };
};
#include "game/Temporal_Game_entity.h"

namespace Temporal::Game
{
    Temporal_Game_Entity::Temporal_Game_Entity(SDL_Texture* texture, SDL_Renderer* renderer)
        : m_entity_renderer(renderer), m_entity_texture(texture)
    {
        m_src_rect = {};
        m_dst_rect = { 32, 32 };
    }

    void Temporal_Game_Entity::render()
    {
        SDL_RenderCopy(m_entity_renderer, m_entity_texture, &m_src_rect, &m_dst_rect);
    }
}
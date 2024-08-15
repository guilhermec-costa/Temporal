#include <iostream>
#include <array>
#include "game/map/Temporal_Tilemap.h"
#include "utils/Temporal_Texture_Manager.h"
#include "game/Temporal_Game.h"
#include "game/constants/Texture_Paths.hpp"

namespace Temporal::Game::Map
{

    Temporal_Tilemap::Temporal_Tilemap(int width, int height, int tile_size)
        : m_map_width(width), m_map_height(height), m_tile_size(tile_size)
    {
        m_tiles_texture_mapper = {
            std::make_pair(0, Temporal::Resources::RED),
            std::make_pair(1, Temporal::Resources::GREEN),
            std::make_pair(2, Temporal::Resources::BLUE)};

        for (auto it = m_tiles_texture_mapper.begin(); it != m_tiles_texture_mapper.end(); it++)
        {
            Temporal_Texture_Manager::get().load(it->second, Temporal_Game::m_renderer->get_renderer());
        }

        m_rows_qty = height / tile_size;
        m_columns_qty = width / tile_size;
    }

    void Temporal_Tilemap::load_map(int _map_data[500])
    {
        for (int row = 0; row < m_rows_qty; row++)
        {
            for (int col = 0; col < m_columns_qty; col++)
            {
                SDL_Rect src_rect;
                src_rect.w = 32;
                src_rect.h = 32;
                src_rect.x = 0;
                src_rect.y = 0;

                SDL_Rect dst_rect;
                dst_rect.x = col * m_tile_size;
                dst_rect.y = row * m_tile_size;
                dst_rect.w = m_tile_size;
                dst_rect.h = m_tile_size;

                int texture_value = _map_data[row * m_columns_qty + col];
                auto it = m_tiles_texture_mapper.find(texture_value);
                Temporal_Tile tile = {
                    src_rect, dst_rect,
                    it->second, true};
                m_tiles[row * m_columns_qty + col] = tile;
            }
        }
    }

    void Temporal_Tilemap::render_map()
    {
        for (int row = 0; row < m_rows_qty; row++)
        {
            for (int col = 0; col < m_columns_qty; col++)
            {
                Temporal_Tile& tile = m_tiles[row * m_columns_qty + col];
                Temporal_Texture_Manager::get().draw(
                    tile.texture_path,
                    tile.dst_rect.x, tile.dst_rect.y,
                    tile.dst_rect.w, tile.dst_rect.h,
                    Temporal_Game::m_renderer->get_renderer());
            }
        }
    }
}
#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "game/map/Temporal_Tile.h"

namespace Temporal::Game::Map
{


    class Temporal_Tilemap
    {
    public:
        Temporal_Tilemap() {};
        Temporal_Tilemap(int width, int height, int tile_size);
        ~Temporal_Tilemap() = default;
        void load_map(int _map_data[500]);
        void render_map();

    private:
        int m_map_width, m_map_height;
        int m_rows_qty, m_columns_qty;
        int m_tile_size;
        Temporal_Tile m_tiles[500];
        std::unordered_map<int, std::string> m_tiles_texture_mapper;
    };
}

using Temporal_Tilemap = Temporal::Game::Map::Temporal_Tilemap;
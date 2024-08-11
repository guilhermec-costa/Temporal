#pragma once
#include <SDL2/SDL_rect.h>
#include <string>

namespace Temporal::Game::Map
{
    struct Temporal_Tile
    {
        SDL_Rect src_rect;
        SDL_Rect dst_rect;
        bool is_walkable;
        std::string texture_path;

        Temporal_Tile() {}
        Temporal_Tile(const SDL_Rect &src_rect, const SDL_Rect &dst_rect,
                      const std::string &texture_path, bool is_walkable)
            : src_rect(src_rect), dst_rect(dst_rect), texture_path(texture_path), is_walkable(is_walkable)
        {
        }
    };
}

using Temporal_Tile = Temporal::Game::Map::Temporal_Tile;
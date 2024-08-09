#include "utils/Temporal_Texture_manager.h"
#include "utils/Temporal_aliases.hpp"
#include <iostream>

namespace Temporal::Utils
{
    SDL_Texture* Temporal_Texture_Manager::load(const char* path, SDL_Renderer* renderer)
    {
        SDL_Surface* sfc = Temporal_Asset_Manager::get().get_asset(path);
        SDL_Texture* txt = SDL_CreateTextureFromSurface(renderer, sfc);
        if(txt == nullptr)
        {
            LOG_ERROR(std::string("Failed to create texture from path: ", path));
            return nullptr;
        }
        m_texture_map[path] = txt;
        return txt;
    }
}
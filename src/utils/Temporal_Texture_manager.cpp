#include "utils/Temporal_Texture_manager.h"
#include "utils/Temporal_Asset_Manager.h"

namespace Temporal::Utils
{
    SDL_Texture* Temporal_Texture_Manager::load(const char* path, SDL_Renderer* renderer)
    {
        SDL_Surface* sfc = Asset_Manager::get().get_asset(path);
        SDL_Texture* txt = SDL_CreateTextureFromSurface(renderer, sfc);
        m_texture_map[path] = txt;
        return txt;
    }
}
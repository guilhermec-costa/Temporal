#include <iostream>
#include "utils/Temporal_Texture_Manager.h"
#include "utils/Temporal_Asset_Manager.h"
#include "utils/Temporal_Logger.h"

namespace Temporal::Utils
{
    SDL_Texture *Temporal_Texture_Manager::load(const std::string &path, SDL_Renderer *renderer)
    {
        auto it = m_texture_map.find(path);
        if (it != m_texture_map.end())
        {
            return it->second;
        }

        SDL_Surface *sfc = Temporal_Asset_Manager::get().get_asset(path);
        SDL_Texture *txt = SDL_CreateTextureFromSurface(renderer, sfc);
        if (txt == nullptr)
        {
            LOG_ERROR(std::string("Failed to create texture from path: ") + path);
            return nullptr;
        }

        LOG_INFO(std::string("Texture created from path: ") + path);
        m_texture_map[path] = txt;
        return txt;
    }

    void Temporal_Texture_Manager::draw(std::string path, const int x, const int y, const int w, const int h, SDL_Renderer *_renderer)
    {
        SDL_Rect src_rect, dst_rect;
        src_rect.x = src_rect.y = 0;
        src_rect.w = dst_rect.w = w;
        src_rect.h = dst_rect.h = h;
        dst_rect.x = x;
        dst_rect.y = y;
        SDL_RenderCopy(_renderer, m_texture_map[path], &src_rect, &dst_rect);
    }

    void Temporal_Texture_Manager::draw(std::string path, const SDL_Rect &src, const SDL_Rect &dst, SDL_Renderer *_renderer)
    {
        SDL_Texture *texture = m_texture_map[path];
        if (texture != nullptr)
            SDL_RenderCopy(_renderer, m_texture_map[path], &src, &dst);
    }
}
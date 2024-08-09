#pragma once
#include "unordered_map"
#include <SDL2/SDL_surface.h>

namespace Temporal::Utils
{
    // class destinated to cache SDL surfaces in memory
    class Asset_Manager
    {
    private:
        Asset_Manager() = default;
        Asset_Manager(const Asset_Manager &) = delete;
        Asset_Manager &operator=(const Asset_Manager &) = delete;
        mutable std::unordered_map<const char *, SDL_Surface *> m_surfaces;

    public:
        static Asset_Manager &get();
        void load_asset(const char *);
        SDL_Surface *get_asset(const char *);
        void clear_from_asset_map(const char *);
    };
}
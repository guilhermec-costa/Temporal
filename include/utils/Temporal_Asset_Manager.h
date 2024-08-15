#pragma once
#include <unordered_map>
#include <string>
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
        std::unordered_map<std::string, SDL_Surface *> m_surfaces_map;

    public:
        static Asset_Manager &get()
        {
            static Asset_Manager instance;
            return instance;
        };
        void load_asset(const std::string& path);
        SDL_Surface *get_asset(const std::string& path);
        void clear_from_asset_map(const std::string& path);
    };
}

using Temporal_Asset_Manager = Temporal::Utils::Asset_Manager;
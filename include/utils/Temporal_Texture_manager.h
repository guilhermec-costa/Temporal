#pragma once
#include "SDL2/SDL_render.h"
#include "unordered_map"
namespace Temporal::Utils
{
    class Temporal_Texture_Manager
    {
    public:
        static Temporal_Texture_Manager &get()
        {
            static Temporal_Texture_Manager instance;
            return instance;
        }

        SDL_Texture *load(const char *path, SDL_Renderer *renderer);

    private:
        Temporal_Texture_Manager() = default;
        Temporal_Texture_Manager(const Temporal_Texture_Manager &ref) = delete;
        Temporal_Texture_Manager &operator=(const Temporal_Texture_Manager &ref) = delete;
        std::unordered_map<const char *, SDL_Texture *> m_texture_map;
    };
}
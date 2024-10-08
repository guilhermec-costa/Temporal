#pragma once
#include <SDL2/SDL.h>

class IWindow {
public:
    virtual void create() = 0;
    virtual void destroy() = 0;
};

namespace Temporal::Game
{
    class Temporal_SDL_Window : public IWindow
    {
    public:
        Temporal_SDL_Window(const char* title, uint32_t w, uint32_t h);
        void create() override;
        void destroy() override;
        SDL_Window* get_window() const;

        uint32_t get_width() const { return m_width; }
        uint32_t get_height() const { return m_heigth; }
    private:
        SDL_Window* m_window;
        uint32_t m_width, m_heigth;
        const char* m_title;
    };
};

using Temporal_SDL_Window = Temporal::Game::Temporal_SDL_Window;
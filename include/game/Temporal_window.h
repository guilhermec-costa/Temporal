#pragma once
#include <SDL2/SDL.h>
#include <variant>
#include <any>

typedef std::variant<SDL_Window*> Win_Types;
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
    private:
        SDL_Window* m_window;
        uint32_t m_width, m_heigth;
        const char* m_title;
    };
};

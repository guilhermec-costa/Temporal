#include <iostream>
#include <SDL2/SDL.h>

#undef main SDL_main

int main(int argc, char* args[])
{
    if(SDL_Init(SDL_INIT_VIDEO))
    std::cout << "hello rpg" << std::endl;
    return 0;
}
#pragma once

#include "imgui/imgui.h"
#include <SDL2/SDL.h>

SDL_Window* make_sdl_window();

class Gui {
public:

    Gui();
    ~Gui();

    void render();
    SDL_Window* window();
  
private:

    void init_sdl();
    void init_glew();
    void init_imgui();
    
    SDL_Window* m_window;
    SDL_GLContext m_gl_context;
};
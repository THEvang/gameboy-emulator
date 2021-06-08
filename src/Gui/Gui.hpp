#pragma once

#include <memory>
#include <functional>

#include "imgui/imgui.h"
#include <SDL2/SDL.h>

using Window_Deleter = std::function<void(SDL_Window*)>;
using Window_Ptr = std::unique_ptr<SDL_Window, Window_Deleter>;
Window_Ptr make_sdl_window();

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
    
    Window_Ptr m_window;
    SDL_GLContext m_gl_context;
};
#pragma once

#include <stdio.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>    // Initialize with glewInit()
#include "Gui/Renderers.hpp"

void init_gui(SDL_Window** window);

class Gui {
public:

    Gui();
    ~Gui();

    void render(GameBoy*);
    SDL_Window* window;
};
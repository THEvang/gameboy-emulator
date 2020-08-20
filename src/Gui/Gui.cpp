#include "Gui/Gui.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
#include <SDL2/SDL.h>
#include <GL/glew.h>    // Initialize with glewInit()
#include <iostream>
#include <string>

Gui::Gui() {

    init_sdl();
    m_window = make_sdl_window();        
    m_gl_context = SDL_GL_CreateContext(m_window.get());
            
    SDL_GL_MakeCurrent(m_window.get(), m_gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    init_glew();
    init_imgui();

}

Gui::~Gui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(m_gl_context);
    SDL_Quit();
}

void Gui::init_sdl() {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        throw Graphics_Init_Error(SDL_GetError());        
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
}

std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> make_sdl_window() {

    const auto window_flags = static_cast<SDL_WindowFlags>(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

    auto window = SDL_CreateWindow("Dear ImGui SDL2+OpenGL3 example", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        1280, 
        720, 
        window_flags);
    

    if(window == nullptr) {
        std::cerr << "Failed to create SDL Window: " << SDL_GetError() << "\n";
        return nullptr;
    }

    const auto window_deleter = [](SDL_Window* window_to_delete) {
        if(window_to_delete != nullptr) {
            SDL_DestroyWindow(window_to_delete);
        }
    };

    return std::unique_ptr<SDL_Window, decltype(window_deleter)>(window, window_deleter);        
}

void Gui::init_glew() {

    auto err = glewInit();
    if (err != GLEW_OK)
    {   
        glewGetErrorString(err);
        throw Graphics_Init_Error(std::to_string(err));
    }
}

void Gui::init_imgui() {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(m_window.get(), m_gl_context);
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(m_window.get());
}

SDL_Window* Gui::window() {
    return m_window.get();
}

void Gui::render() {
    
    auto io = ImGui::GetIO();
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    // Rendering
    ImGui::Render();
    glViewport(0, 0, static_cast<int>(io.DisplaySize.x), static_cast<int>(io.DisplaySize.y));
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(m_window.get());
}

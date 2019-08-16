#pragma once

#include <memory>
#include <MemoryMap.h>

#include <SDL2/SDL.h>

class Ppu {
public:
    Ppu(std::shared_ptr<MemoryMap> mainMemory)
        : m_mainMemory(mainMemory) {

        SDL_CreateWindowAndRenderer(256, 256, 0, &window, &renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawPoint(renderer, 128, 128);
        SDL_RenderPresent(renderer);
    };

    ~Ppu() {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
    };
    
private:

    std::shared_ptr<MemoryMap> m_mainMemory;

    SDL_Window* window;
    SDL_Renderer* renderer;
};
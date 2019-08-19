#include <Cartridge.h>
#include <GameBoy.h>
#include <Ppu.h>

#include <iostream>
#include <memory>

#include<Logger.h>

#include <SDL2/SDL.h>

int main() {

    Logger::logging = Logging::On;
    GameBoy gameboy;

    try {
        
        auto pokemonBlue = std::make_shared<Cartridge>("rom/cpu_instrs.gb");
        gameboy.InsertCartridge(pokemonBlue);

    } catch (const InsertCartrigdeException& insertCartrigdeException) {
        std::cerr << insertCartrigdeException.what();
        return -1;
    }

    gameboy.PowerOn();

    return 1;
}
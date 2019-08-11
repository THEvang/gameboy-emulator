#include <Cartridge.h>
#include <GameBoy.h>

#include <iostream>
#include <memory>

int main() {

    GameBoy gameboy;

    try {
        
        auto pokemonBlue = std::make_shared<Cartridge>("pokemonBlue.gb");
        gameboy.InsertCartridge(pokemonBlue);

    } catch (const InsertCartrigdeException& insertCartrigdeException) {
        std::cerr << insertCartrigdeException.what();
        return -1;
    }

    gameboy.PowerOn();

    return 1;
}
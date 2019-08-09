#include <Cartridge.h>
#include <GameBoy.h>

#include <iostream>

int main() {


    try {
        Cartridge pokemonBlue("pokemonBlue.gb");
    } catch (const InsertCartrigdeException& insertCartrigdeException) {
        std::cerr << insertCartrigdeException.what();
        return -1;
    }

    return 1;
}
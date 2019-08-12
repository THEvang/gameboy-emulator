#include <GameBoy.h>

#include <iostream>

GameBoy::GameBoy() {}


void GameBoy::InsertCartridge(std::shared_ptr<Cartridge> cartridge) {
    
    m_cartridge = cartridge;
    m_cartridge->Meta();

    m_mainMemory = std::make_shared<MemoryMap>(cartridge);
    m_cpu = std::make_unique<Cpu>(m_mainMemory);
}

void GameBoy::RemoveCartridge() {

}

void GameBoy::PowerOn() {

    std::string a;
    while(true) {

        std::cin.get();
        m_cpu->Execute();
    }
}

void GameBoy::PowerOff() {

}

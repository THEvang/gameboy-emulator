#include <GameBoy.h>

#include <iostream>

GameBoy::GameBoy()
    : m_mainMemory(std::make_shared<MemoryMap>(nullptr))
    , m_cpu(m_mainMemory) {  
}

void GameBoy::InsertCartridge(std::unique_ptr<Cartridge> cartridge) {
    
    m_cartridge = std::move(cartridge);
    m_cartridge->Meta();
}

void GameBoy::RemoveCartridge() {

}

void GameBoy::PowerOn() {

    std::string a;
    while(true) {

        std::cin >> a;
        m_cpu.Execute();
    }
}

void GameBoy::PowerOff() {

}

#include <GameBoy.h>

GameBoy::GameBoy()
    : m_mainMemory(std::make_shared<std::vector<uint8_t>>(0xFFFF))
    , m_cpu(m_mainMemory) {  
}

void GameBoy::InsertCartridge(std::unique_ptr<Cartridge> cartridge) {
    
    m_cartridge = std::move(cartridge);
}

void GameBoy::RemoveCartridge() {

}

void GameBoy::PowerOn() {

}

void GameBoy::PowerOff() {

}

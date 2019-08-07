#include <Cartridge.h>

#include<iostream>
#include <fstream>

Cartridge::Cartridge(const std::string& path) {

    std::ifstream src(path, std::ios::in | std::ios::binary | std::ios::ate);

        if(src.is_open())
        {
            auto size = src.tellg();
            src.seekg(0, std::ios::beg);
            m_memory = new char [size];
            src.read(m_memory, size);

            for (auto i = 0; i < size; i++) {
                m_bitmemory.push_back(m_memory[i]);
            }

        } else {
            std::cout << "Failed to open file \n";
        }
}

Cartridge::~Cartridge() {
        delete[] m_memory;
}

std::vector<std::bitset<8>> Cartridge::GetMemory() const {
        return m_bitmemory;
}


void Cartridge::Meta() {

        std::cout << "Game: ";
        for (auto addr = 0x0134; addr <= 0x142; addr++) {
            std::cout << char(m_bitmemory[addr].to_ullong());
            
        }
        std::cout << "\n";

        std::cout << "Gameboy Type: ";
        
        switch(m_bitmemory[0x143].to_ullong()) {
            case 0x80:
                std::cout << "Gameboy Color\n";
                break;
            default:
                std::cout << "Gameboy\n";
                break;
        }
        
        std::cout << "GB/SGB Status: ";
        switch (m_bitmemory[0x146].to_ullong())
        {
        case 0:
            std::cout << "GameBoy\n";
            break;
        
        default:
            std::cout << "Super GameBoy\n";
            break;
        }

        std::cout << m_bitmemory[0x147].to_ullong()  << "\n";

        std::cout << "Destination Code: ";
        switch (m_bitmemory[0x149].to_ullong())
        {
        case 0:
            std::cout << "Japanese\n";
            break;
        
        default:
            std::cout << "Non Japanese\n";
            break;
        }

        std::cout << "ROM size:";
        switch(m_bitmemory[0x148].to_ullong()) {
            case 0:
                std::cout << "32KByte\n";
                break;
            case 1:
                std::cout << "64KByte\n";
                break;
            case 2:
                std::cout << "128Kbyte\n";
                break;
            case 3:
                std::cout << "256KByte\n";
                break;
            case 4:
                std::cout << "512KByte\n";
                break;
            case 5:
                std::cout << "1MByte\n";
                break;
            case 6:
                std::cout << "2MByte\n";
                break;
            case 0x52:
                std::cout << "1.1MByte\n";
                break;
            case 0x53:
                std::cout << "1.2MByte\n";
                break;
            default:
                std::cout << "1.5MByte\n";
                break;
        }
    }

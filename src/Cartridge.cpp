#include <Cartridge.h>

#include<iostream>
#include <fstream>

InsertCartrigdeException::InsertCartrigdeException(const std::string& message)
    : runtime_error(message)
{}

Cartridge::Cartridge(const std::string& path) {

    std::ifstream src(path, std::ios::in | std::ios::binary | std::ios::ate);

        if(src.is_open())
        {
            auto size = src.tellg();
            src.seekg(0, std::ios::beg);
            
            auto memory = new char [size];
            src.read(memory, size);

            for (auto i = 0; i < size; i++) {
                m_memory.push_back(memory[i]);
            }

            delete[] memory;

        } else {
            throw InsertCartrigdeException("Failed to load cartridge: " + path + "\n");
        }
}


std::vector<uint8_t> Cartridge::GetMemory() const {
        return m_memory;
}


void Cartridge::Meta() {

        std::cout << "Game: ";
        for (auto addr = 0x0134; addr <= 0x142; addr++) {
            std::cout << char(m_memory[addr]);
            
        }
        std::cout << "\n";

        std::cout << "Gameboy Type: ";
        
        switch(m_memory[0x143]) {
            case 0x80:
                std::cout << "Gameboy Color\n";
                break;
            default:
                std::cout << "Gameboy\n";
                break;
        }
        
        std::cout << "GB/SGB Status: ";
        switch (m_memory[0x146])
        {
        case 0:
            std::cout << "GameBoy\n";
            break;
        
        default:
            std::cout << "Super GameBoy\n";
            break;
        }

        std::cout << "Cartridge Type: ";
        switch(m_memory[0x147]) {
            case 0x00:
                std::cout << "ROM Only\n";
                break;
            
            case 0x01:
                std::cout << "ROM + MBC1\n";
                break;
            
            case 0x02:
                std::cout << "ROM + MBC1 + RAM\n";
                break;
            
            case 0x03:
                std::cout << "ROM + MBC1 + RAM + BATT\n";
                break;
            
            case 0x05:
                std::cout << "ROM + MBC2\n";
                break; 
            
            case 0x06:
                std::cout << "ROM + MBC2 + BATTERY\n";
                break;
            
            case 0x08:
                std::cout << "ROM + RAM\n";
                break;
            
            case 0x09:
                std::cout << "ROM + RAM + BATTERY\n";
                break;
            
            case 0x0B:
                std::cout << "ROM + MMM01\n";
                break;
            
            case 0x0C:
                std::cout << "ROM + MMM01 + SRAM\n";
                break;
            
            case 0x0D:
                std::cout << "ROM + MMM01 + SRAM + BATTERY\n";
                break;
            
            case 0x12:
                std::cout << "ROM + MBC3 + RAM";
                break;
            
            case 0x13:
                std::cout << "ROM + MBC3 + RAM + BATTERY\n";
                break;
            
            case 0x19:
                std::cout << "ROM + MBC3\n";
                break;

            case 0x1A:
                std::cout << "ROM + MBC3 + RAM\n";
                break;
            
            case 0x1B:
                std::cout << "ROM + MBC5 + RAM + BATTERY\n";
                break;
            
            case 0x1C:
                std::cout << "ROM + MBC5 + RUMBLE\n";
                break;
            
            case 0x1D:
                std::cout << "ROM + MBC5 + RUMBLE + SRAM\n";
                break;
            
            case 0x1E:
                std::cout << "ROM + MBC5 + RUMBLE + SRAM + BATTERY\n";
                break;
            
            case 0x1F:
                std::cout << "Pocket Camera\n";
                break;
            
            case 0xFD:
                std::cout << "Bandai TAMA5\n";
                break;
            
            case 0xFE:
                std::cout << "Hudson HuC - 3\n";
                break;

            default:
                std::cout << "N/A\n";
                break;

        }


        std::cout << "Destination Code: ";
        switch (m_memory[0x149])
        {
        case 0:
            std::cout << "Japanese\n";
            break;
        
        default:
            std::cout << "Non Japanese\n";
            break;
        }

        std::cout << "ROM size:";
        switch(m_memory[0x148]) {
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

        std::cout << "RAM Size: ";

        switch(m_memory[0x0149]) {
            case 0:
                std::cout << "None\n";
                break;
            
            case 1:
                std::cout << "16 kBit = 2 kB = 1 Bank\n";
                break;
            
            case 2:
                std::cout << "64 kBit = 8 kB = 1 Bank\n";
                break;
            
            case 3:
                std::cout << "256 kBit = 32 kB = 4 Banks\n";
                break;
            
            case 4:
                std::cout << "1 MBit = 128 kB = 16 Banks\n";
                break;
            
            default: 
                std::cout << "N/A";
                break;

        }

        std::cout << "Licensee code: ";
        
        switch (m_memory[0x14B]) {
            case 0x33:
                std::cout << "Check 0144/0145 for lincensee code\n";
                break;

            case 0x79:
                std::cout << "Accolade\n";
                break;
            
            case 0xA4:
                std::cout << "Konami\n";
                break; 

        }
    }

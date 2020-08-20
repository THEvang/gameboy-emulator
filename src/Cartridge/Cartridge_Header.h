#include <string>
#include <cstdint>
#include <array>
#include <filesystem>

#include "Memory_Bank_Type.h"

struct Cartridge_Header {

    bool is_super_gameboy = false;
    Memory_Bank_Type memory_bank_type;
    int rom_banks = 0;
    int ram_size = 0;
};

Cartridge_Header peek_header(const std::string& rom_path) {
        
    constexpr int header_size = 0x14F - 0x100;
    std::array<header_size, uint8_t> buffer;

    if(!std::experimental::filesystem::exists(path)) {
        return {};
    }

    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return {};
    }

    file.seekg(0x100);
    file.read(buffer, header_size);
    
    return buffer;
}
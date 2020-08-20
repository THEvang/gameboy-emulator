#pragma once

#include <string>
#include <bitset>
#include <vector>
#include <array>

#include <stdexcept>

enum class Bank_Type {
    Rom_Only,
    MBC_1,
    MBC_2,
    MBC_3,
    MBC_5,
    MBC_6,
    MBC_7,
    Uknown,
};

Bank_Type get_bank_type(uint8_t type_number);
bool has_ram(uint8_t type_number);
int rom_size(uint8_t rom_size_identifier);

std::vector<uint8_t> load_cartridge(const std::string& path);

std::size_t rom_size();
std::size_t ram_size();
Bank_Type bank_type();
bool is_sgb();

struct Header {
    std::array<uint8_t, 0x14F - 0x100> m_data;
};

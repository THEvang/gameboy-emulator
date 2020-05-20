#pragma once 
#include <string>

enum class ROMSize {
    
};

enum class DestinationCode {
    Japanese,
    NonJapanese
};

enum class CartridgeType {
    ROM_ONLY,
    MBC1,
    MBC2_RAM,
};

struct Rom {
    const std::string title;
    const std::string manufacturerCode;
    const bool is_color_gameboy;
    const bool is_super_gameboy;
    CartridgeType cartiridge_type;

    ROMSize romSize;
    DestinationCode destinationCode;
};
#include "Memory/Ram.h"


uint8_t Ram::read(uint16_t address) const {

}

void Ram::write(uint16_t address, uint8_t data) {

}


uint16_t map_to_ram_address(uint16_t address, int bank_numnber) {
    constexpr auto ram_start = 0xA000;

    
} 
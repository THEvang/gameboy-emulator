#include <cstddef>
#include <array>

template <std::size_t N>
class Ram {

    uint8_t read(uint16_t address) const;
    void write(uint16_t address, uint8_t data);
    
private:

    std::array<uint8_t, N> m_ram;
    int m_bank_number = 0;
};

uint16_t map_to_ram_address(uint16_t address, int bank_number);
#pragma once

#include <cstdint>
#include <vector>

class Memory {
public:

    Memory(std::vector<uint8_t> memory);

    uint8_t read(const uint16_t address) const;
    void write(const uint16_t address, const uint8_t value);

private:

    std::vector<uint8_t> m_memory;

};
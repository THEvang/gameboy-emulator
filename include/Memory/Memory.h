#pragma once

#include <cstdint>
#include <vector>

struct Address {
    uint16_t value;
};


class Memory {
public:

    explicit Memory(const std::vector<uint8_t>& memory);
    explicit Memory(const int size);

    uint8_t read(const uint16_t address) const;
    void write(const uint16_t address, const uint8_t value);

private:

    std::vector<uint8_t> m_memory;
};
#pragma once

#include <cstdint>
#include <vector>

class Memory {
public:

    explicit Memory(const std::vector<uint8_t>& memory);
    explicit Memory(const int size);

    [[nodiscard]] uint8_t read(uint16_t address) const noexcept;
    void write(uint16_t address, uint8_t value);

private:

    std::vector<uint8_t> m_memory;
};
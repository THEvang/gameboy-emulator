#include <cstdint>
#include <array>

class Memory {
public:

    uint8_t read(const uint16_t address) const;
    void write(const uint16_t address, const uint8_t value);

private:

    std::array<uint8_t, 0xFFFF> m_memory;
};
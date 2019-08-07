#pragma once

#include <string>
#include <bitset>
#include <vector>

class Cartridge
{
public:
    Cartridge(const std::string& path);
    ~Cartridge();

    std::vector<std::bitset<8>> GetMemory() const;

    void Meta();

private:

    std::vector<std::bitset<8>> m_bitmemory;

    char* m_memory;
};


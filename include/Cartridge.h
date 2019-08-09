#pragma once

#include <string>
#include <bitset>
#include <vector>

#include <stdexcept>

class InsertCartrigdeException : public std::runtime_error {
public:
    InsertCartrigdeException(const std::string& message);
};


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


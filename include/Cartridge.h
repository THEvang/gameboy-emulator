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

    std::vector<uint8_t> GetMemory() const;

    void Meta();

private:

    std::vector<uint8_t> m_memory;

};


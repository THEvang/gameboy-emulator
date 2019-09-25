#pragma once

#include <string>
#include <bitset>
#include <vector>

#include <stdexcept>

class InsertCartrigdeException : public std::runtime_error {
public:
    InsertCartrigdeException(std::string const & message);
};


class Cartridge
{
public:
    Cartridge(std::string const & path);

    std::vector<uint8_t> GetMemory() const;

    void Meta();

private:

    std::vector<uint8_t> m_memory;

};


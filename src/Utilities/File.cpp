#include "Utilities/File.hpp"

#include <fstream>
#include <iterator>

std::vector<uint8_t> load_rom(const std::string& path) {

    std::ifstream file(path, std::ios::binary);
    std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});

    return buffer;
}
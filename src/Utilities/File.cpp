#include "Utilities/File.hpp"

#include <fstream>
#include <iterator>

std::optional<std::vector<uint8_t>> load_rom(const std::filesystem::path& path) {
    
    if(!std::filesystem::exists(path)) {
        return {};
    }

    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return {};
    }

    std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});

    return buffer;
}
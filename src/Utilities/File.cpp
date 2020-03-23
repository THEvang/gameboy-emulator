#include <File.h>

#include <fstream>
#include <iterator>

std::experimental::optional<std::vector<uint8_t>> load_rom(const std::experimental::filesystem::path& path) {
    
    if(!std::experimental::filesystem::exists(path)) {
        return {};
    }

    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return {};
    }

    std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});

    return buffer;
}
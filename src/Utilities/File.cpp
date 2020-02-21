#include <File.h>

#include <fstream>
#include <iterator>

std::vector<uint8_t> load_rom(const std::string& path) {
    
    std::ifstream file("../tests/gb-test-roms/cpu_instrs/cpu_instrs.gb", std::ios::binary);
    if (!file.is_open()) {
        return {};
    }

    std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});

    return buffer;
}

void memory_banK_type(std::vector<uint8_t> rom) {

};
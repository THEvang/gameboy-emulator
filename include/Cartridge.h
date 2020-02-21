#pragma once

#include <string>
#include <bitset>
#include <vector>

#include <stdexcept>

struct CartridgeHeader {

};

std::vector<uint8_t> load_cartridge(const std::string& path);



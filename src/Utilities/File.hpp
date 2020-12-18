#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <optional>
#include <filesystem>

std::optional<std::vector<uint8_t>> load_rom(const std::filesystem::path& path);
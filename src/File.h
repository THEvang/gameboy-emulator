#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <experimental/optional>
#include <experimental/filesystem>

std::experimental::optional<std::vector<uint8_t>> load_rom(const std::experimental::filesystem::path& path);
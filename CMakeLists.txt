cmake_minimum_required(VERSION 3.15)
project(Gameboy
    VERSION 1.0
    DESCRIPTION "Gameboy emulator"
    LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(project_warnings INTERFACE)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

add_library(gb-core)
target_include_directories(gb-core PRIVATE src)
target_link_libraries(gb-core PRIVATE project_warnings)

add_executable(gb-emu)
target_include_directories(gb-emu PRIVATE src)
target_link_libraries(gb-emu PRIVATE project_warnings gb-core ncurses SDL2)

add_subdirectory(src)
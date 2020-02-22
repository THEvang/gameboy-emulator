cmake_minimum_required(VERSION 3.1..3.15)
set(CMAKE_BUILD_TYPE Debug)
project(Gameboy
    VERSION 1.0
    DESCRIPTION "Gameboy emulator"
    LANGUAGES CXX)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy" "-checks=cppcoreguidelines-*,clang-analyzer-*,modernize-*,performance-*, readability-*")

add_executable(Gameboy.out main.cpp)
target_compile_options(Gameboy.out PRIVATE -Wall)

add_subdirectory(src/Cpu)
add_subdirectory(src/Memory)
add_subdirectory(src/Utilities)
add_subdirectory(src/Gameboy)
add_subdirectory(src/imgui)


target_include_directories(Gameboy.out PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(Gameboy.out PRIVATE Gameboy Cpu Memory Utils ImgGui SDL2 GLEW GLU GL)



add_library(cpu STATIC)
target_include_directories(cpu PRIVATE ./)

add_library(imgui STATIC)
target_include_directories(imgui PRIVATE ./)

add_library(memory STATIC)
target_include_directories(memory PRIVATE ./)

add_library(utilities STATIC)
target_include_directories(utilities PRIVATE ./)

add_library(gameboy STATIC)
target_include_directories(gameboy PRIVATE ./)

add_library(graphics STATIC)
target_include_directories(graphics PRIVATE ./)

add_library(gui STATIC)
target_include_directories(gui PRIVATE ./)

add_library(input STATIC)
target_include_directories(input PRIVATE ./)

add_library(disassembler STATIC)
target_include_directories(disassembler PRIVATE ./)

add_executable(Gameboy.out main.cpp)
target_include_directories(Gameboy.out PRIVATE ./ ./)
target_link_libraries(Gameboy.out PRIVATE gui memory input gameboy imgui utilities cpu graphics disassembler)
target_link_libraries(Gameboy.out PRIVATE SDL2 GLEW GL pthread  ${CMAKE_DL_LIBS})

add_subdirectory(Input)
add_subdirectory(Cpu)
add_subdirectory(Gameboy)
add_subdirectory(imgui)
add_subdirectory(Memory)
add_subdirectory(Utilities)
add_subdirectory(Graphics)
add_subdirectory(Gui)
add_subdirectory(Disassembler)

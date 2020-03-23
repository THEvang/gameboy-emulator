add_library(cpu STATIC)
target_include_directories(cpu PRIVATE ../include)

add_library(imgui STATIC)
target_include_directories(imgui PRIVATE ../include/imgui)

add_library(memory STATIC)
target_include_directories(memory PRIVATE ../include)

add_library(utilities STATIC)
target_include_directories(utilities PRIVATE ../include)

add_library(gameboy STATIC)
target_include_directories(gameboy PRIVATE ../include)

add_executable(Gameboy.out main.cpp Gui.h)
target_include_directories(Gameboy.out PRIVATE ../include ../include/imgui)
target_link_libraries(Gameboy.out PRIVATE gameboy imgui utilities memory cpu )

add_subdirectory(Cpu)
add_subdirectory(Gameboy)
add_subdirectory(imgui)
add_subdirectory(Memory)
add_subdirectory(Utilities)
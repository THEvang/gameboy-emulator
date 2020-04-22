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

add_library(graphics STATIC)
target_include_directories(graphics PRIVATE ../include)

add_library(gui STATIC)
target_include_directories(gui PRIVATE ../include)

add_executable(Gameboy.out main.cpp)
target_include_directories(Gameboy.out PRIVATE ../include ../include/imgui)
target_link_libraries(Gameboy.out PRIVATE gameboy imgui utilities memory cpu graphics gui)
target_link_libraries(Gameboy.out PRIVATE SDL2 GLEW GL pthread)

add_subdirectory(Cpu)
add_subdirectory(Gameboy)
add_subdirectory(imgui)
add_subdirectory(Memory)
add_subdirectory(Utilities)
add_subdirectory(graphics)
add_subdirectory(gui)
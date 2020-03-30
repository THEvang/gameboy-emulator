cmake_minimum_required(VERSION 3.15)
set(CMAKE_BUILD_TYPE Debug)
project(Gameboy
    VERSION 1.0
    DESCRIPTION "Gameboy emulator"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   

add_library(project_warnings INTERFACE)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(cmake/StaticAnalyzers.cmake)
add_subdirectory(src)

# target_include_directories(Gameboy.out PUBLIC ${CMAKE_SOURCE_DIR}/include)
# target_link_libraries(Gameboy.out PRIVATE Gameboy Cpu Memory Utils ImgGui SDL2 GLEW GLU GL)
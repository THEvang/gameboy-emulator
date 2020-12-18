cmake_minimum_required(VERSION 3.15)
set(CMAKE_BUILD_TYPE Debug)
project(Gameboy
    VERSION 1.0
    DESCRIPTION "Gameboy emulator"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/StaticAnalyzers.cmake)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(project_warnings INTERFACE)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

add_library(gb-core)
target_include_directories(gb-core PRIVATE src)

add_library(gb-gui)
target_include_directories(gb-gui PRIVATE src)

add_executable(gb-emu)
target_include_directories(gb-emu PRIVATE src)
target_link_libraries(gb-emu PRIVATE project_warnings)

add_executable(tests)
target_include_directories(tests PRIVATE ${CMAKE_INCLUDE_DIRS_CATCH2})

target_link_libraries(gb-emu PRIVATE gb-gui gb-core)
target_link_libraries(gb-emu PRIVATE SDL2 GLEW GL pthread  ${CMAKE_DL_LIBS})

add_subdirectory(src)
add_subdirectory(tests)
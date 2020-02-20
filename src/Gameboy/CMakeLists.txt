add_library(Gameboy Gameboy.cpp)
target_include_directories(Gameboy PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(Gameboy PRIVATE -Wall)

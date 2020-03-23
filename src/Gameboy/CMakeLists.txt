add_library(Gameboy Gameboy.cpp)
target_include_directories(Gameboy PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(Gameboy PRIVATE project_warnings)

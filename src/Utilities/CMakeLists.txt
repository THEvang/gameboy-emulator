
set(CMAKE_CXX_CLANG_TIDY "clang-tidy" "-checks=clang-analyzer-*,bugprone-*,modernize-*,performance-*")

add_library(Utils BitOperations.cpp File.cpp)
set_property(TARGET Utils PROPERTY CMAKE_CXX_STANDARD 17)
target_include_directories(Utils PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(Utils PRIVATE -Wall -std=c++17)

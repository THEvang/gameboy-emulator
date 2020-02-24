set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy" "-checks=clang-analyzer-*,bugprone-*,modernize-*,performance-*")

add_library(Memory Memory.cpp MBC1.cpp MBC2.cpp)
target_include_directories(Memory PUBLIC ${CMAKE_SOURCE_DIR}/include)
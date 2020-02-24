set(CMAKE_CXX_CLANG_TIDY "clang-tidy" "-checks=clang-analyzer-*,bugprone-*,modernize-*,performance-*")
add_library(Cpu Cpu.cpp Operations.cpp)
target_include_directories(Cpu PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(Cpu PRIVATE -Wall)

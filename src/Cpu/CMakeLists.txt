add_library(Cpu Cpu.cpp Operations.cpp CBOperations.cpp Timer.cpp)
target_include_directories(Cpu PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(Cpu PRIVATE -Wall)

add_library(cpu Cpu.cpp)
target_include_directories(cpu PUBLIC ../include)
target_compile_options(cpu PRIVATE -Wall -Wextra -Werror)

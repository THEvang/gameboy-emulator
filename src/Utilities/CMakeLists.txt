target_sources(utilities 
    PRIVATE
    BitOperations.cpp 
    File.cpp
)
target_compile_options(utilities PRIVATE -Wall -std=c++17)
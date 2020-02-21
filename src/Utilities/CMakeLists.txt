add_library(Utils BitOperations.cpp File.cpp)
target_include_directories(Utils PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(Utils PRIVATE -Wall)

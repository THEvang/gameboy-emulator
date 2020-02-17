add_library(Utils BitOps.cpp)
target_include_directories(Utils PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(Utils PRIVATE -Wall -Wextra -Werror)

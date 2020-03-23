
target_sources(
    memory 
    PRIVATE
    Memory.cpp 
    MBC1.cpp 
    MBC2.cpp
)
target_link_libraries(memory PRIVATE project_warnings)
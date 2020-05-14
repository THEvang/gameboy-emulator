
target_sources(
    memory 
    PRIVATE
    Memory.cpp 
    Memory_Controller.cpp
    Cartridge.cpp
)
target_link_libraries(memory PRIVATE project_warnings)
target_sources(disassembler PRIVATE
    Disassembler.cpp)

target_link_libraries(cpu PRIVATE project_warnings)
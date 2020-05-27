target_sources(cpu
    PRIVATE
    
    Cpu.cpp
    Operations.cpp 
    CBOperations.cpp 
    Timer.cpp
    Interrupt_Handler.cpp
    Interpreter.cpp
)

target_compile_options(cpu PRIVATE -Wall)
target_link_libraries(cpu PRIVATE project_warnings)
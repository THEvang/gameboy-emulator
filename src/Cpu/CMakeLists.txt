target_sources(cpu
    PRIVATE
    
    Cpu.cpp
    Operations.cpp 
    CBOperations.cpp 
    Timer.cpp
    Interrupt_Handler.cpp
    Interpreter.cpp
)

target_compile_features(cpu PRIVATE cxx_std_17)
target_link_libraries(cpu PRIVATE project_warnings)
set_target_properties(cpu PROPERTIES CXX_STANDARD 17)
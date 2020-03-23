target_sources(cpu
    PRIVATE
    
    Cpu.cpp
    Operations.cpp 
    CBOperations.cpp 
    Timer.cpp
)

target_compile_options(cpu PRIVATE -Wall)
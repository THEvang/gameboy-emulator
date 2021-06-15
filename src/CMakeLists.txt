target_sources(gb-emu 
    PRIVATE
    main.c)
    
add_subdirectory(Input)
add_subdirectory(Cpu)
add_subdirectory(Gameboy)
add_subdirectory(Memory)
add_subdirectory(Utilities)
add_subdirectory(Graphics)
add_subdirectory(Gui)
add_subdirectory(Disassembler)
add_subdirectory(Cpu)
add_subdirectory(Gameboy)
add_subdirectory(Memory)
add_subdirectory(Utilities)
add_subdirectory(Graphics)
add_subdirectory(Disassembler)

target_sources(gb-emu PRIVATE
    Emulator.h
    Registers.h
    gb-emu.c
)

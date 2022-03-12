add_subdirectory(App)
add_subdirectory(Cpu)
add_subdirectory(Gameboy)
add_subdirectory(Memory)
add_subdirectory(Utilities)
add_subdirectory(Graphics)
add_subdirectory(Disassembler)
add_subdirectory(InputHandlers)
add_subdirectory(Renderers)

target_sources(gb-emu PRIVATE
    Emulator.h
    Emulator.c
    Registers.h
)
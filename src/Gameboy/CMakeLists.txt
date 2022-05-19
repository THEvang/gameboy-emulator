target_sources(gb-core
    PRIVATE
    Gameboy.h
    Gameboy.c

    Cartridge.h
    Cartridge.c
)

target_sources(rom-inspector
    PRIVATE
    Cartridge.h
    Cartridge.c
)

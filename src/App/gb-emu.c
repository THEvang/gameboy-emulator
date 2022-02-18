#include <stdio.h>
#include <unistd.h>

#include "Gameboy/Cartridge.h"
#include "Emulator.h"

void gb_usage(void) {
    printf("Usage: gb-emu [options] rom\n");
    printf("  Options:\n");
    printf("    -i,\t Inspect rom without running the emulator\n");
    printf("    -h,\t Display this help message\n");
}

int main(int argc, char* argv[]) {

    const char* options = "ihv";
    int opt;
    bool print_info = false;
    while( (opt = getopt(argc, argv, options)) != -1) {
        switch (opt) {
            case 'h':
            case '?':
                gb_usage();
                return 1;
            case 'i':
                print_info = true;
                break;
        }
    }

    if (optind >= argc) {
        gb_usage();
        return 1;
    }

    char* rom_path = argv[optind];

    GameboyRom rom;
    if(gb_load_rom(&rom, rom_path)) {
        printf("ERROR\tFailed loading rom\t%s\n", rom_path);
        return 1;
    }

    CartridgeHeader header;
    gb_parse_header(&rom, &header);

    if(print_info) {
        gb_print_header(&header);
        return 0;
    }

    Emulator emulator;
    gb_init_emulator(&rom, &header, &emulator);
    gb_run_emulator(&emulator);

    emulator.input_handler_cleanup();
    emulator.render_cleanup(emulator.renderer);

    return 0;
}
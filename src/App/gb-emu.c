#include <stdio.h>
#include <unistd.h>

#include "Utilities/File.h"
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

    gb_Rom rom;
    load_rom(&rom, rom_path);

    CartridgeHeader header;
    gb_parse_header(&rom, &header);

    if (!rom.data) {
        printf("Unable to find Rom: %s\n", rom_path);
        return 1;
    }

    if(print_info) {
        gb_print_header(&header);
        return 0;
    }

    Emulator emulator;
    gb_init_emulator(&rom, &header, &emulator);

    RenderState render_state = emulator.render_init();
    emulator.input_handler_init();

    gb_run_emulator(&emulator, render_state);

    emulator.input_handler_cleanup();
    emulator.render_cleanup(render_state);

    return 0;
}
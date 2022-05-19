#include <stdio.h>

#include "Gameboy/Cartridge.h"

void 
gb_print_header(CartridgeHeader* header) {

    printf("%s\n", header->title);

    header->color_gameboy_only ? printf("COLOR GAMEBOY SUPPORT: Color Gameboy Only\n")
        : printf("COLOR GAMEBOY SUPPORT: Gameboy and Color Gameboy\n");

    header->super_gameboy_support ? printf("SUPER GAMEBOY SUPPORT: Yes\n")
        : printf("SUPER GAMEBOY SUPPORT: No\n");

    printf("CARTRIDGE TYPE: ");
    switch (header->type) {
        case MB_ROM_ONLY:
            printf("Rom\n");
            break;
        case MB_MBC_1:
            printf("MBC 1\n");
            break;
        case MB_MBC_2:
            printf("MBC 2\n");
            break;
        case MB_MBC_3:
            printf("MBC_3\n");
            break;
        case MB_MBC_5:
            printf("MBC 5\n");
            break;
        case MB_MBC_6:
            printf("MBC 6\n");
            break;
        case MB_MBC_7:
            printf("MBC 7\n");
            break;
        case MB_MM01:
            printf("MM01\n");
            break;
        case MB_HUC1:
            printf("HuC 1\n");
            break;
        case MB_HUC3:
            printf("HuC 3\n");
            break;
        case MB_POCKET_CAMERA:
            printf("Pocket Camera\n");
            break;
        case MB_BANDAI_TAMA5:
            printf("Bandai Tama 5\n");
            break;
        case MB_UNKNOWN:
        default:
            printf("Unknow\n");
            break;
    }

    printf("ROM SIZE: %dKByte\n", header->rom_size);
    printf("RAM SIZE: %dKByte\n", header->ram_size);
    
    printf("DESTINATION: ");
    header->destination == DST_JAPAN ? printf("Japan") : printf("World");
    printf("\n");
}

int
main(int argc, char* argv[]) {

	if (argc != 2) {
		printf("usage: rom-inspector rom\n");
		return 1;
	}

	GameboyRom rom;
	if (gb_load_rom(&rom, argv[1])) {
		printf("ERROR: Failed loading rom %s\n", argv[1]);
		return 1;
	}

	CartridgeHeader header;
	gb_parse_header(&rom, &header);
	gb_print_header(&header);

	return 0;
}

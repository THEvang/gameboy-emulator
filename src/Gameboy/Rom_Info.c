#include "Rom_Info.h"

#include <stdio.h>

Memory_Bank_Type get_memory_bank_type(gb_Rom* rom) {
    switch(rom->data[0x0147]) {
        case 0x00: case 0x08: case 0x09:
            return MB_None;
        case 0x01: case 0x02: case 0x03:
            return MB_MBC_1;
        case 0x05: case 0x06:
            return MB_MBC_2;
        case 0x0B: case 0x0C: case 0x0D:
            return MB_MM01;
        case 0x0F: case 0x10: case 0x11: case 0x12: case 0x13:
            return MB_MBC_3;
        case 0x19: case 0x1A: case 0x1B: case 0x1C: case 0x1D:
        case 0x1E:
            return MB_MBC_5;
        case 0x20:
            return MB_MBC_6;
        case 0x22:
            return MB_MBC_7;
        default:
            return MB_None;
    }
}

void gb_print_rom_info(gb_Rom* rom) {

    for(int i = 0x0134; i <= 0x0143; i++) {
        printf("%c", rom->data[i]);
    }
    printf("\n");

    switch(rom->data[0x143]) {
        case 0x80:
            printf("Color Gameboy Support: Gameboy and Color Gameboy\n");
            break;
        case 0xC0:
            printf("Color Gameboy Support: Color Gameboy Only\n");
            break;
        default:
            printf("Color Gameboy Support: Unknown\n");
            break;       
    }

    switch (rom->data[0x0146]) {
        case 0x00:
            printf("Super Gameboy Support: No\n");
            break;
        case 0x03:
            printf("Super Gameboy Support: Yes\n");
            break;
        default:
            printf("Super Gameboy Support: Unknown\n");
            break;
    }

    printf("Cartridge Type: ");
    switch(rom->data[0x0147]) {
        case 0x00:
            printf("Rom ONLY\n");
            break;
        case 0x01:
            printf("MBC 1\n");
            break;
        case 0x02:
            printf("MBC 1 + Ram\n");
            break;
        case 0x03:
            printf("MBC 1 + Ram + Battery\n");
            break;
        case 0x05:
            printf("MBC 2\n");
            break;
        case 0x06:
            printf("MBC2 + Battery\n");
            break;
        case 0x08:
            printf("Rom + Ram\n");
            break;
        case 0x09:
            printf("Rom + Ram + Battery\n");
            break;
        case 0x0B:
            printf("MMM01\n");
            break;
        case 0x0C:
            printf("MMM01 + Ram\n");
            break;
        case 0x0D:
            printf("MMM01 + Ram + Battery\n");
            break;
        case 0x0F:
            printf("MBC3 + Timer + Battery\n");
            break;
        case 0x10:
            printf("MBC3 + Timer + Ram + Battery\n");
            break;
        case 0x11:
            printf("MBC3\n");
            break;
        case 0x12:
            printf("MBC3 + Ram\n");
            break;
        case 0x13:
            printf("MBC3 + Ram + Battery\n");
            break;
        case 0x19:
            printf("MBC5\n");
            break;
        case 0x1A:
            printf("MB5 + Ram\n");
            break;
        case 0x1B:
            printf("MBC5 + Ram + Battery\n");
            break;
        case 0x1C:
            printf("MBC5 + Rumble\n");
            break;
        case 0x1D:
            printf("MBC5 + Rumble + Ram\n");
            break;
        case 0x1E:
            printf("MBC5 + Rumble + Ram + Battery\n");
            break;
        case 0x20:
            printf("MBC6\n");
            break;
        case 0x22:
            printf("MBC7 + Sensor + Rumble + Ram + Battery\n");
            break;
        case 0xFC:
            printf("Pocket Camera\n");
            break;
        case 0xFD:
            printf("Bandai Tama5\n");
            break;
        case 0xFE:
            printf("HuC3\n");
            break;
        case 0xFF:
            printf("HuC1 + Ram + Battery\n");
            break;
    }

    printf("ROM SIZE: ");
    switch (rom->data[0x0148]) {
        case 0x00:
            printf("32kb - 2 Banks\n");
            break;
        case 0x01:
            printf("64kb - 4 Banks\n");
            break;
        case 0x02:
            printf("128kb - 8 Banks\n");
            break;
        case 0x03:
            printf("256kb - 16 Banks\n");
            break;
        case 0x04:
            printf("512kb - 32 Banks\n");
            break;
        case 0x05:
            printf("1Mb - 64 Banks\n");
            break;
        case 0x06:
            printf("2MByte - 128 Banks\n");
            break;
        case 0x07:
            printf("4MByte - 256 Banks\n");
            break;
        case 0x08:
            printf("8MByte - 512 Banks\n");
            break;
        case 0x52:
            printf("1.1MByte - 72 Banks\n");
            break;
        case 0x53:
            printf("1.2MByte - 80 Banks\n");
            break;
        case 0x54:
            printf("1.5Mbyte - 96 Banks\n");
            break;
        default:
            printf("Unknown\n");
            break;
    }

    printf("RAM SIZE: ");
    switch (rom->data[0x0149]) {
        case 0x00:
            printf("0 - No Ram\n");
            break;
        case 0x01:
            printf("2kb\n");
            break;
        case 0x02:
            printf("8kb\n");
            break;
        case 0x03:
            printf("32kb - 4 Banks\n");
            break;
        case 0x04:
            printf("128kb - 16 Banks\n");
            break;
        case 0x05:
            printf("64kb - 8 Banks\n");
            break;
        default:
            printf("Unknown\n");
            break;
    }
}
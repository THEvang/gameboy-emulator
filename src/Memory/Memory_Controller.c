#include "Memory/Memory_Controller.h"
#include "Utilities/BitOperations.h"
#include "Memory_Banks.h"

#include <stdio.h>
#include <stdlib.h>

void gb_memory_set_initial_state(MemoryBankController* mc, CartridgeHeader* header) {

    switch(header->type) {
        case MB_ROM_ONLY:
            mc->read = gb_read_none;
            mc->write = gb_write_none;
            break;
        case MB_MBC_1:
            mc->read = gb_read_mbc_1;
            mc->write = gb_write_mbc_1;
            break;
        case MB_MBC_3:
            mc->read = gb_read_mbc_3;
            mc->write = gb_write_mbc_3;
            break;
        case MB_MBC_5:
            mc->read = gb_read_mbc_5;
            mc->write = gb_write_mbc_5;
            break;
        default:
            mc->read = gb_read_mbc_1;
            mc->write = gb_write_mbc_1;
            break;
    }

    mc->write(mc, 0xFF00, 0x3F);
    mc->write(mc, 0xFF04, 0xCC);
    mc->write(mc, 0xFF05, 0);
    mc->write(mc, 0xFF06, 0);
    mc->write(mc, 0xFF07, 0);

    mc->write(mc, 0xFF10, 0x80);
    mc->write(mc, 0xFF11, 0xBF);
    mc->write(mc, 0xFF12, 0xF3);

    mc->write(mc, 0xFF14, 0xBF);
    mc->write(mc, 0xFF16, 0x3F);
    mc->write(mc, 0xFF17, 0x00);
    mc->write(mc, 0xFF19, 0xBF);

    mc->write(mc, 0xFF1A, 0x7F);
    mc->write(mc, 0xFF1B, 0xFF);
    mc->write(mc, 0xFF1C, 0x9F);
    mc->write(mc, 0xFF1E, 0xBF);

    mc->write(mc, 0xFF20, 0xFF);
    mc->write(mc, 0xFF21, 0x00);
    mc->write(mc, 0xFF22, 0x00);
    mc->write(mc, 0xFF23, 0xBF);
    mc->write(mc, 0xFF24, 0x77);
    mc->write(mc, 0xFF25, 0xF3);
    mc->write(mc, 0xFF26, 0xF1);

    mc->write(mc, 0xFF40, 0x91);
    mc->write(mc, 0xFF42, 0x00);
    mc->write(mc, 0xFF43, 0x00);
    mc->write(mc, 0xFF45, 0x00);
    mc->write(mc, 0xFF47, 0xFC);
    mc->write(mc, 0xFF48, 0xFF);
    mc->write(mc, 0xFF49, 0xFF);

    mc->write(mc, 0xFF4A, 0x00);
    mc->write(mc, 0xFF4B, 0x00);
    mc->write(mc, 0xFFFF, 0x00);

    mc->banking_register_1 = 1;
    mc->banking_register_2 = 0;
    mc->rom_bank_mask = header->rom_banks - 1;
    mc->ram_bank_mask = header->rom_banks == 1 ? header->rom_banks :
        header->rom_banks -1;

    mc->ram_enabled = false;
    mc->banking_mode = Banking_Mode_ROM;
    mc->buttons = 0xFF;
}
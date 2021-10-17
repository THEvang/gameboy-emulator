#include "Memory/Memory_Controller.h"
#include "Utilities/BitOperations.h"
#include "Memory_Banks.h"

#include <stdio.h>
#include <stdlib.h>

#define ROM_BANK_SIZE 0x4000
#define RAM_BANK_SIZE 0x2000

void set_io(MemoryBankController* mc,  Memory_Bank_Type mb_type) {

    switch(mb_type) {
        case MB_None:
            mc->read = gb_read_none;
            mc->write = gb_write_none;
            return;
        case MB_MBC_1:
            mc->read = gb_read_mbc_1;
            mc->write = gb_write_mbc_1;
            return;
        case MB_MBC_5:
            mc->read = gb_read_mbc_5;
            mc->write = gb_write_mbc_5;
            return;
        default:
            mc->read = gb_read_mbc_1;
            mc->write = gb_write_mbc_1;
            return;
    }
}
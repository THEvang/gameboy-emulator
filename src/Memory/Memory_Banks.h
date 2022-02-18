#pragma once

#include <stdint.h>
#include "Memory_Controller.h"

void gb_dma_transfer(MemoryBankController* mc, uint8_t data);
void gb_set_rom_bank_number(MemoryBankController* mc, uint8_t data, uint8_t bank_type_mask);
void gb_set_ram_bank_number(MemoryBankController* mc, uint8_t data);
void gb_set_banking_mode(MemoryBankController* mc, uint8_t data);

uint8_t gb_read_joypad_input(MemoryBankController* mc);

uint8_t gb_read_none(MemoryBankController* mc, uint16_t address);
void gb_write_none(MemoryBankController* mc, uint16_t address, uint8_t data);

uint8_t gb_read_mbc_1(MemoryBankController* mc, uint16_t address);
void gb_write_mbc_1(MemoryBankController* mc, uint16_t address, uint8_t data);

uint8_t gb_read_mbc_2(MemoryBankController* mc, uint16_t address);
void gb_write_mbc_2(MemoryBankController* mc, uint16_t address, uint8_t data);

uint8_t gb_read_mbc_3(MemoryBankController* mc, uint16_t address);
void gb_write_mbc_3(MemoryBankController* mc, uint16_t address, uint8_t data);

uint8_t gb_read_mbc_5(MemoryBankController* mc, uint16_t address);
void gb_write_mbc_5(MemoryBankController* mc, uint16_t address, uint8_t data);
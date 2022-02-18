#pragma once

#include <stdint.h>
#include "Cpu.h"
#include "Memory/Memory_Controller.h"

//Addressing Modes
void implied(Cpu*);
uint8_t immediate_byte(Cpu*, MemoryBankController*);
uint16_t immediate_word(Cpu*, MemoryBankController*);
uint8_t hl_addressing(Cpu*, MemoryBankController*);
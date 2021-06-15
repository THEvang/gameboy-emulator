#pragma once

#include <stdint.h>
#include "Cpu.h"

//Addressing Modes
void implied(Cpu*);
uint8_t immediate_byte(Cpu*);
uint16_t immediate_word(Cpu*);
uint8_t hl_addressing(Cpu*);
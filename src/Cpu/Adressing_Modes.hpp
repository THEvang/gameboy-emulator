#pragma once

#include <stdint.h>
#include <functional>

#include "Cpu.h"

typedef union Operand {
    uint8_t byte;
    uint16_t word;
} Operand;

using Address_Mode = std::function<Operand(Cpu&)>;

//Addressing Modes
Operand implied(Cpu&);
Operand immediate(Cpu&);
Operand immediate_extended(Cpu&);
Operand hl_addressing(Cpu&);
Operand extended_address(Cpu&);
Operand none(Cpu&);
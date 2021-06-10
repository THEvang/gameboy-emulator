#pragma once

#include <stdint.h>
#include <variant>
#include "Cpu.h"

using Operand = std::variant<uint8_t, uint16_t, int8_t>;

//Addressing Modes
Operand implied(Cpu&);
Operand immediate(Cpu&);
Operand immediate_extended(Cpu&);
Operand hl_addressing(Cpu&);
Operand relative_address(Cpu&);
Operand extended_address(Cpu&);
Operand implied(Cpu&);
Operand indexed_address(Cpu&);
Operand extended_addressing(Cpu&);
Operand none(Cpu&);
#pragma once

#include <stdint.h>
#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef union Operand {
    uint8_t byte;
    uint16_t word;
} Operand;

typedef Operand (*Address_Mode)(Cpu*);

//Addressing Modes
Operand implied(Cpu*);
Operand immediate(Cpu*);
Operand immediate_extended(Cpu*);
Operand hl_addressing(Cpu*);
Operand extended_address(Cpu*);
Operand none(Cpu*);
Operand cb_addressing(Cpu*);


#ifdef __cplusplus
}
#endif
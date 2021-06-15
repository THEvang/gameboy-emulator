#pragma once

#include "Cpu/Opcodes.h"
#include "Cpu/CBOpcodes.h"

int gb_disassemble(Opcode opcode);
int gb_disassemble_cb(CB_Code opcode);
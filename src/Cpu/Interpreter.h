#pragma once

#include "Cpu/Cpu.h"
#include "Cpu/Opcodes.h"
#include "Cpu/CBOpcodes.h"

int gb_execute(Opcode opcode, Cpu* cpu);
int gb_execute_cb(CB_Code opcode, Cpu* cpu);
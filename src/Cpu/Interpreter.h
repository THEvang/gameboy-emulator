#pragma once

#include "Cpu/Cpu.h"
#include "Cpu/Opcodes.h"
#include "Cpu/CBOpcodes.h"

int execute(Opcode opcode, Cpu* cpu);
int execute_cb(CB_Code opcode, Cpu* cpu);
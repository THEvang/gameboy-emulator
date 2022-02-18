#pragma once

#include "Cpu/Cpu.h"
#include "Cpu/Opcodes.h"
#include "Cpu/CBOpcodes.h"
#include "Memory/Memory_Controller.h"

int gb_execute(Opcode opcode, Cpu* cpu, MemoryBankController* mc);
int gb_execute_cb(CB_Code opcode, Cpu* cpu, MemoryBankController* mc);
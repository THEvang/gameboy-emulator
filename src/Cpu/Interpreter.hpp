#pragma once

#include <functional>
#include "Cpu/Cpu.h"

#include "Cpu/Opcodes.hpp"
#include "Cpu/CBOpcodes.hpp"
#include "Adressing_Modes.h"

using Operation = std::function<int(Cpu&, Operand&)>;

struct Instruction {
    Operation execute;
    Address_Mode read_operand;
};

Instruction fetch(Opcode opcode);
Instruction fetch_cb(CBCode opcode);
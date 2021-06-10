#pragma once

#include <functional>
#include <variant>

#include "Cpu/Cpu.h"

#include "Cpu/Opcodes.hpp"
#include "Cpu/CBOpcodes.hpp"

using Operand = std::variant<uint8_t, uint16_t, int8_t>;
using Address_Mode = std::function<Operand(Cpu&)>;
using Operation = std::function<int(Cpu&, Operand&)>;

struct Instruction {
    Operation execute;
    Address_Mode read_operand;
};

Instruction fetch(Opcode opcode);
Instruction fetch_cb(CBCode opcode);
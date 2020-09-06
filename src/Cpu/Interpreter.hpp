#pragma once

#include <functional>
#include <exception>
#include <string>

#include "Cpu/Cpu.hpp"

#include "Cpu/Opcodes.hpp"
#include "Cpu/CBOpcodes.hpp"

class UnimplementedOperation : public std::runtime_error {
public:
    explicit UnimplementedOperation(const std::string& msg)
        : runtime_error(msg) {
    }
};

using Operand = std::variant<uint8_t, uint16_t, int8_t>;
using Operation = std::function<int(Cpu&, Operand)>;

struct Instruction {
    Address_Mode read_operand;
    Operation execute;
};

Instruction fetch(Opcode opcode);
Instruction fetch_cb(CBCode opcode);
#include <string>

#include "Cpu/Opcodes.hpp"
#include "Cpu/CBOpcodes.hpp"

struct Instruction {
    Opcode opcode;
    std::string name;
    int cycles;
};

Instruction disassemble(Opcode const& opcode);
Instruction disassemble_cb(CBCode const& opcode);
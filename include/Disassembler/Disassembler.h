#include <string>
#include <vector>

#include "Cpu/Opcodes.h"

struct Instruction {
    Opcode opcode;
    const std::string name;
    int cycles;
};


Instruction disassemble(Opcode const& opcode);
Instruction disassemble_cb(Opcode const& opcode);
#include <string>

#include "Cpu/Opcodes.h"
#include "Cpu/CBOpcodes.h"

struct Instruction {
    Opcode opcode;
    std::string name;
    int cycles;
};

Instruction disassemble(Opcode const& opcode);
Instruction disassemble_cb(CBCode const& opcode);
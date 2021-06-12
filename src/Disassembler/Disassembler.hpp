#include <string>

#include "Cpu/Opcodes.h"
#include "Cpu/CBOpcodes.h"

struct Instruction_Info {
    Opcode opcode;
    std::string name = {"Hello There"};
    int cycles;
};

Instruction_Info disassemble(Opcode const& opcode);
Instruction_Info disassemble_cb(CBCode const& opcode);
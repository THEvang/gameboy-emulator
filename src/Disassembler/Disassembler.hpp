#include <string>

#include "Cpu/Opcodes.hpp"
#include "Cpu/CBOpcodes.hpp"

struct Instruction_Info {
    Opcode opcode;
    std::string name = {"Hello There"};
    int cycles;
};

Instruction_Info disassemble(Opcode const& opcode);
Instruction_Info disassemble_cb(CBCode const& opcode);
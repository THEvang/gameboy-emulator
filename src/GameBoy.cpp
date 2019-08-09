#include <GameBoy.h>
#include <Opcodes.h>

GameBoy::GameBoy()
    : m_mainMemory(0xFFFF) {
        m_programCounter = 0x0100;
}

void GameBoy::Emulate() {

    Byte opcode = m_mainMemory[m_programCounter];

    switch(opcode) {
        case 0x00:
            NoOperation();
            break;
        case 0x01:
            LoadRegister(m_regC, m_mainMemory[opcode+1]);
            LoadRegister(m_regB, m_mainMemory[opcode+2]);
            m_programCounter += 2;
            break;

        case 0x02:
            UnimplementedOperation("LD  BC, d16");
            break;

        case 0x03:
            UnimplementedOperation("INC BC");
            break;
        
        case 0x04:
            m_regB++;
            if (m_regB == 0) {
                m_regF.set(7, true);
                m_regF.set(6, false);
            }
            break;
        
        case 0x05:
            UnimplementedOperation("DEC B");
            break;

        case 0x06:
            LoadRegister(m_regB, m_mainMemory[opcode++]);
            break;
        
        case 0x07:
            UnimplementedOperation("RLCA");
            break;

        case 0x08:
            UnimplementedOperation("LD (a16), SP");
            break;

        case 0x09:
        {
            auto bc = CombineRegisters(m_regB, m_regC);
            auto hl = CombineRegisters(m_regH, m_regL);
            auto sum = hl + bc;
            UnimplementedOperation("ADD HL, BC");
            break;
        }
        case 0x0A:
            UnimplementedOperation("LD A, (BC)");
            break;

        case 0x0B:
            UnimplementedOperation("DEC BC");
            break;
        
        case 0x0C:
            UnimplementedOperation("INC C");
            break;
        
        case 0x0D:
            UnimplementedOperation("DEC C");
            break;
        
        case 0x0E:
            UnimplementedOperation("LD C, d8");
            break;
        
        case 0x0F:
            UnimplementedOperation("RRCA");
            break;
        
        case 0x10:
            UnimplementedOperation("STOP");
            break;

        case 0x11:
            UnimplementedOperation("LD DE, d16");
            break;
        
        case 0x12:
            UnimplementedOperation("LD (DE), A");
            break;
        
        case 0x13:
            UnimplementedOperation("INC DE");
            break;
        
        case 0x14:
            UnimplementedOperation("INC D");
            break;
        
        case 0x15:
            UnimplementedOperation("DEC D");
            break;
        
        case 0x16:
            UnimplementedOperation("LD D, d8");
            break;
        
        case 0x17:
            UnimplementedOperation("RLA");
            break;

        case 0x18:
            UnimplementedOperation("JR r8");
            break;
        
        case 0x19:
            UnimplementedOperation("ADD, HL, DE");
            break;
        
        case 0x1A:
            UnimplementedOperation("LD A, (DE)");
            break;
        
        case 0x1B:
            UnimplementedOperation("DEC DE");
            break;
        
        case 0x1C:
            UnimplementedOperation("INC E");
            break;

        case 0x1D:
            UnimplementedOperation("DEC E");
            break;
        
        case 0x1E:
            UnimplementedOperation("LD E, d8");
            break;
        
        case 0x1F:
            UnimplementedOperation("RRA");
            break;

        case 0x20:
            UnimplementedOperation("JR NZ,r8");
            break;
        
        case 0x21:
            UnimplementedOperation("LD HL,d16");
            break;
        
        case 0x22:
            UnimplementedOperation("LD (HL+), A");
            break;
        
        case 0x23:
            UnimplementedOperation("INC HL");
            break;

        case 0x24:
            UnimplementedOperation("INC H");
            break;
        
        case 0x25:
            UnimplementedOperation("DEC H");
            break;
        
        case 0x26:
            UnimplementedOperation("LD H, d8");
            break;
        
        case 0x27:
            UnimplementedOperation("DAA");
            break;
        
        case 0x28:
            UnimplementedOperation("JR Z, r8");
            break;
        
        case 0x29:
            UnimplementedOperation("ADD HL, HL");
            break;
        
        case 0x2A:
            UnimplementedOperation("LD A, (HL+)");
            break;
        
        case 0x2B:
            UnimplementedOperation("DEC HL");
            break;
        
        case 0x2C:
            UnimplementedOperation("INC L");
            break;
        
        case 0x2D:
            UnimplementedOperation("DEC L");
            break;
        
        case 0x2E:
            UnimplementedOperation("LD L, d8");
            break;
        
        case 0x2F:
            UnimplementedOperation("CPL");
            break;
        
        case 0x30:
            UnimplementedOperation("JR NZ, r8");
            break;
        
        case 0x31:
            UnimplementedOperation("LD SP, d16");
            break;
        
        case 0x32:
            UnimplementedOperation("LD (HL+), A");
            break;
        
        case 0x33:
            UnimplementedOperation("INC SP");
            break;
        
        case 0x34:
            UnimplementedOperation("INC HL");
            break;
        
        case 0x35:
            UnimplementedOperation("DEC HL");
            break;
        
        case 0x36:
            UnimplementedOperation("LD (HL), d8");
            break;
        
        case 0x37:
            UnimplementedOperation("SCF");
            break;
        
        case 0x38:
            UnimplementedOperation("JR C, r8");
            break;
        
        case 0x39:
            UnimplementedOperation("ADD HL, SP");
            break;
        
        case 0x3A:
            UnimplementedOperation("LD A, (HL-)");
            break;
        
        case 0x3B:
            UnimplementedOperation("DEC SP");
            break;
        
        case 0x3C:
            UnimplementedOperation("INC A");
            break;
        
        case 0x3D:
            UnimplementedOperation("DEC A");
            break;
        
        case 0x3E: 
            UnimplementedOperation("LD A, d8");
            break;

        case 0x3F:
            UnimplementedOperation("CCF");
            break;
        
        case 0x40:
            LoadRegister(m_regB, m_regB);
            break;
        
        case 0x41:
            LoadRegister(m_regB, m_regC);
            break;
        
        case 0x42:
            LoadRegister(m_regB, m_regD);
            break;
        
        case 0x43:
            LoadRegister(m_regB, m_regE);
            break;
        
        case 0x44:
            LoadRegister(m_regB, m_regH);
            break;
        
        case 0x45:
            LoadRegister(m_regB, m_regL);
            break;
        
        case 0x46:
            UnimplementedOperation("LD B, (HL)");
            break;
        
        case 0x47:
            LoadRegister(m_regB, m_regA);
            break;
        
        case 0x48:
            LoadRegister(m_regC, m_regB);
            break;
        
        case 0x49:
            LoadRegister(m_regC, m_regC);
            break;
        
        case 0x4A:
            LoadRegister(m_regC, m_regD);
            break;
        
        case 0x4B:
            LoadRegister(m_regC, m_regE);
            break;
        
        case 0x4C:
            LoadRegister(m_regC, m_regH);
            break;
        
        case 0x4D:
            LoadRegister(m_regC, m_regL);
            break;
        
        case 0x4E:
            UnimplementedOperation("LOAD C, (HL)");
            break;
        
        case 0x4F:
            LoadRegister(m_regC, m_regA);
            break;

        case 0x50:
            LoadRegister(m_regD, m_regB);
            break;

        case 0x51:
            LoadRegister(m_regD, m_regC);
            break;

        case 0x52:
            LoadRegister(m_regD, m_regD);
            break;

        case 0x53:
            LoadRegister(m_regD, m_regE);
            break;

        case 0x54:
            LoadRegister(m_regD, m_regH);
            break;

        case 0x55:
            LoadRegister(m_regD, m_regL);
            break;

        case 0x56:
            UnimplementedOperation("LD D, (HL)");
            break;

        case 0x57:
            LoadRegister(m_regD, m_regA);
            break;

        case 0x58:
            LoadRegister(m_regE, m_regB);
            break;

        case 0x59:
            LoadRegister(m_regE, m_regC);
            break;

        case 0x5A:
            LoadRegister(m_regE, m_regD);
            break;

        case 0x5B:
            LoadRegister(m_regE, m_regE);
            break;

        case 0x5C:
            LoadRegister(m_regE, m_regH);
            break;

        case 0x5D:
            LoadRegister(m_regE, m_regL);
            break;

        case 0x5E:
            UnimplementedOperation("LD, E, (HL)");
            break;

        case 0x5F:
            LoadRegister(m_regE, m_regA);
            break;

        case 0x60:
            LoadRegister(m_regH, m_regB);
            break;

        case 0x61:
            LoadRegister(m_regH, m_regC);
            break;

        case 0x62:
            LoadRegister(m_regH, m_regD);
            break;

        case 0x63:
            LoadRegister(m_regH, m_regE);
            break;

        case 0x64:
            LoadRegister(m_regH, m_regH);
            break;

        case 0x65:
            LoadRegister(m_regH, m_regL);
            break;

        case 0x66:
            UnimplementedOperation("LD H, (HL)");
            break;

        case 0x67:
            LoadRegister(m_regH, m_regA);
            break;

        case 0x68: 
            LoadRegister(m_regL, m_regB);
            break;
        
        case 0x69:
            LoadRegister(m_regL, m_regC);
            break;
        
        case 0x6A:
            LoadRegister(m_regL, m_regD);
            break;
        
        case 0x6B:
            LoadRegister(m_regL, m_regE);
            break;
        
        case 0x6C:
            LoadRegister(m_regL, m_regH);
            break;
        
        case 0x6D:
            LoadRegister(m_regL, m_regL);
            break;
        
        case 0x6E:
            UnimplementedOperation("LD L, (HL)");
            break;
        
        case 0x6F:
            LoadRegister(m_regL, m_regA);
            break;
        
        case 0x70:
            UnimplementedOperation("LD (HL), B");
            break;
        
        case 0x71:
            UnimplementedOperation("LD (HL), C");
            break;
        
        case 0x72:
            UnimplementedOperation("LD (HL), D");
            break;
        
        case 0x73: 
            UnimplementedOperation("LD, (HL), E");
            break;
        
        case 0x74:
            UnimplementedOperation("LD (HL), H");
            break;
        
        case 0x75:
            UnimplementedOperation("LD (HL), L");
            break;
        
        case 0x76:
            UnimplementedOperation("HALT");
            break;
        

        case 0x77:
            UnimplementedOperation("LD (HL), A");
            break;
        
        case 0x78:
            LoadRegister(m_regA, m_regB);
            break;
        
        case 0x79:
            LoadRegister(m_regA, m_regC);
            break;
        
        case 0x7A:
            LoadRegister(m_regA, m_regD);
            break;
        
        case 0x7B:
            LoadRegister(m_regA, m_regE);
            break;
        
        case 0x7C:
            LoadRegister(m_regA, m_regH);
            break;
        
        case 0x7D:
            LoadRegister(m_regA, m_regL);
            break;
        
        case 0x7E:
            UnimplementedOperation("LD A, (HL)");
            break;
        
        case 0x7F:
            LoadRegister(m_regA, m_regA);
            break;
        
        case 0x80:
            AddRegisters(m_regA, m_regB, m_regF);
            break;
        
        case 0x81:
            AddRegisters(m_regA, m_regC, m_regF);
            break;
        
        case 0x82:
            AddRegisters(m_regA, m_regD, m_regF);
            break;

        case 0x83:
            AddRegisters(m_regA, m_regE, m_regF);
            break;
        
        case 0x84:
            AddRegisters(m_regA, m_regH, m_regF);
            break;
        
        case 0x85:
            AddRegisters(m_regA, m_regL, m_regF);
            break;
        
        case 0x86:
            UnimplementedOperation("ADD A, (HL)");
            break;

        case 0x87:
            AddRegisters(m_regA, m_regA, m_regF);
            break;

        case 0x88:
            UnimplementedOperation("ADC A, B");
            break;

        case 0x89:
            UnimplementedOperation("ADC, A, C");
            break;

        case 0x8A:
            UnimplementedOperation("ADC A, D");
            break;
        
        case 0x8B:
            UnimplementedOperation("ADC A, E");
            break;
        
        case 0x8C:
            UnimplementedOperation("ADC A, H");
            break;
        
        case 0x8D:
            UnimplementedOperation("ADC, A, L");
            break;
        
        case 0x8E:
            UnimplementedOperation("ADC A, (HL)");
            break;
        
        case 0x8F:
            UnimplementedOperation("ADC A, A");
            break;
        
        case 0x90:
            UnimplementedOperation("SUB B");
            break;
        
        case 0x91:
            UnimplementedOperation("SUB C");
            break;
        
        case 0x92:
            UnimplementedOperation("SUB D");
            break;
        
        case 0x93:
            UnimplementedOperation("SUB E");
            break;
        
        case 0x94:
            UnimplementedOperation("SUB H");
            break;
        
        case 0x95:
            UnimplementedOperation("SUB L");
            break;
        
        case 0x96:
            UnimplementedOperation("SUB (HL)");
            break;
        
        case 0x97:
            UnimplementedOperation("SUB A");
            break;
        
        case 0x98:
            UnimplementedOperation("SBC A, B");
            break;
        
        case 0x99:
            UnimplementedOperation("SBC A, C");
            break;
        
        case 0x9A:
            UnimplementedOperation("SBC A, D");
            break;
        
        case 0x9B:
            UnimplementedOperation("SBC A, E");
            break;
        
        case 0x9C:
            UnimplementedOperation("SBC A, H");
            break;
        
        case 0x9D:
            UnimplementedOperation("SBC, A, L");
            break;
        
        case 0x9E:
            UnimplementedOperation("SBC A, (HL)");
            break;

        case 0x9F:
            UnimplementedOperation("SBC A, A");
            break;
        
        case 0xA0:
            UnimplementedOperation("AND B");
            break;
        
        case 0xA1:
            UnimplementedOperation("AND C");
            break;
        
        case 0xA2:
            UnimplementedOperation("AND D");
            break;
        
        case 0xA3:
            UnimplementedOperation("AND E");
            break;
        
        case 0xA4:
            UnimplementedOperation("AND H");
            break;
        
        case 0xA5:
            UnimplementedOperation("AND L");
            break;
        
        case 0xA6:
            UnimplementedOperation("AND (HL)");
            break;
        
        case 0xA7:
            UnimplementedOperation("AND A");
            break;
        
        case 0xA8:
            UnimplementedOperation("XOR B");
            break;
        
        case 0xA9:
            UnimplementedOperation("XOR C");
            break;
        
        case 0xAA:
            UnimplementedOperation("XOR D");
            break;
        
        case 0xAB:
            UnimplementedOperation("XOR E");
            break;
        
        case 0xAC:
            UnimplementedOperation("XOR H");
            break;
        
        case 0xAD:
            UnimplementedOperation("XOR L");
            break;
        
        case 0xAE:
            UnimplementedOperation("XOR (HL)");
            break;
        
        case 0xAF:
            UnimplementedOperation("XOR A");
        
        case 0xB0:
            UnimplementedOperation("OR B");
            break;
        
        case 0xB1:
            UnimplementedOperation("OR C");
            break;
        
        case 0xB2:
            UnimplementedOperation("OR D");
            break;
        
        case 0xB3:
            UnimplementedOperation("OR E");
            break;
        
        case 0xB4:
            UnimplementedOperation("OR H");
            break;
        
        case 0xB5:
            UnimplementedOperation("OR L");
            break;
        
        case 0xB6:
            UnimplementedOperation("OR (HL)");
            break;
        
        case 0xB7:
            UnimplementedOperation("OR A");
            break;
        
        case 0xB8:
            UnimplementedOperation("CP B");
            break;
        
        case 0xB9:
            UnimplementedOperation("CP C");
            break;
        
        case 0xBA:
            UnimplementedOperation("CP D");
            break;
        
        case 0xBB:
            UnimplementedOperation("CP E");
            break;
        
        case 0xBC:
            UnimplementedOperation("CP H");
            break;
        
        case 0xBD:
            UnimplementedOperation("CP L");
            break;
        
        case 0xBE:
            UnimplementedOperation("CP (HL)");
            break;
        
        case 0xBF:
            UnimplementedOperation("CP A");
            break;
        
        case 0xC0:
            UnimplementedOperation("RET NZ");
            break;
        
        case 0xC1:
            UnimplementedOperation("POP BC");
            break;
        
        case 0xC2:
            UnimplementedOperation("JP NZ, a16");
            break;
        
        case 0xC3:
            UnimplementedOperation("JP a16");
            break;
        
        case 0xC4:
            UnimplementedOperation("CALL NZ, a16");
            break;
        
        case 0xC5:
            UnimplementedOperation("PUSH BC");
            break;
        
        case 0xC6:
            UnimplementedOperation("ADD A, d8");
            break;
        
        case 0xC7:
            UnimplementedOperation("RST 00H");
            break;
        
        case 0xC8:
            UnimplementedOperation("RET Z");
            break;
        
        case 0xC9:
            UnimplementedOperation("RET");
            break;
        
        case 0xCA:
            UnimplementedOperation("JP Z, a16");
            break;
        
        case 0xCB:
            UnimplementedOperation("PREFIX CB");
            break;
        
        case 0xCC: 
            UnimplementedOperation("CALL Z, a16");
            break;
        
        case 0xCD:
            UnimplementedOperation("CALL a16");
            break;
        
        case 0xCE:
            UnimplementedOperation("ADC A, d8");
            break;
        
        case 0xCF:
            UnimplementedOperation("RST 08H");
            break;
        
        case 0xD0:
            UnimplementedOperation("RET NC");
            break;
        
        case 0xD1:
            UnimplementedOperation("POP DE");
            break;
        
        case 0xD2:
            UnimplementedOperation("JP NC, a16");
            break;
        
        case 0xD3:
            UnimplementedOperation("Unsupported opcode");
            break;
        
        case 0xD4:
            UnimplementedOperation("CALL NC, a16");
            break;
        
        case 0xD5:
            UnimplementedOperation("PUSH DE");
            break;
        
        case 0xD6:
            UnimplementedOperation("SUB d8");
            break;
        
        case 0xD7:
            UnimplementedOperation("RST 10H");
            break;
        
        case 0xD8:
            UnimplementedOperation("RET C");
            break;
        
        case 0xD9:
            UnimplementedOperation("RETI");
            break;
        
        case 0xDA:
            UnimplementedOperation("JP C, a16");
            break;
        
        case 0xDB: 
            UnimplementedOperation("Unsupported opcode");
            break;
        
        case 0xDC:
            UnimplementedOperation("CALL C, a16");
            break;
        
        case 0xDD:
            UnimplementedOperation("Unsupported opcode");
            break;
        
        case 0xDE:
            UnimplementedOperation("SBC A, d8");
            break;
        
        case 0xDF:
            UnimplementedOperation("RST 18H");
            break;
        
        case 0xE0:
            UnimplementedOperation("LDH (a8), A");
            break;
        
        case 0xE1:
            UnimplementedOperation("POP HL");
            break;
        
        case 0xE2:
            UnimplementedOperation("LD (C), A");
            break;
        
        case 0xE3:
            UnimplementedOperation("Unsupported opcode");
            break;
        
        case 0xE4:
            UnimplementedOperation("Unsupported opcode");
            break;
        
        case 0xE5:
            UnimplementedOperation("PUSH HL");
            break;
        
        case 0xE6:
            UnimplementedOperation("AND d8");
            break;
        
        case 0xE7:
            UnimplementedOperation("RST 20H");
            break;
        
        case 0xE8:
            UnimplementedOperation("ADD SP, r8");
            break;
        
        case 0xE9:
            UnimplementedOperation("JP (HL)");
            break;
        
        case 0xEA:
            UnimplementedOperation("LD (a16), A");
            break;
        
        case 0xEB:
            UnimplementedOperation("Unsupported opcode");
            break;
        
        case 0xEC:
            UnimplementedOperation("Unsupported opcode");
            break;
        
        case 0xED:
            UnimplementedOperation("Unsupported opcode");
            break;
        
        case 0xEE:
            UnimplementedOperation("XOR d8");
            break;
        
        case 0xEF:
            UnimplementedOperation("RST 28H");
            break;
        
        case 0xF0:
            UnimplementedOperation("LDH A, (a8)");
            break;
        
        case 0xF1:
            UnimplementedOperation("POP AF");
            break;
        
        case 0xF2:
            UnimplementedOperation("LD A, (C)");
            break;
        
        case 0xF3:
            UnimplementedOperation("DI");
            break;
        
        case 0xF4:
            UnimplementedOperation("Unsupported opcode");
            break;
        
        case 0xF5:
            UnimplementedOperation("PUSH AF");
            break;
        
        case 0xF6:
            UnimplementedOperation("OR d8");
            break;
        
        case 0xF7:
            UnimplementedOperation("RST 30H");
            break;
        
        case 0xF8:
            UnimplementedOperation("LD HL, SP+r8");
            break;
        
        case 0xF9:
            UnimplementedOperation("LD SP, HL");
            break;
        
        case 0xFA:
            UnimplementedOperation("LD A, (a16)");
            break;
        
        case 0xFB:
            UnimplementedOperation("EI");
            break;
        
        case 0xFC:
            UnimplementedOperation("Unsupported opcode");
            break;
        
        case 0xFD:
            UnimplementedOperation("Unsupported opcode");
            break;
        
        case 0xFE:
            UnimplementedOperation("CP d8");
            break;
        
        case 0xFF:
            UnimplementedOperation("RST 38H");
            break;

        default:
            UnimplementedOperation("Invalid Opcode");
    }

    opcode++;

}
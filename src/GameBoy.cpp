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

        default:
            UnimplementedOperation("Invalid Opcode");
    }

    opcode++;

}
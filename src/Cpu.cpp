#include <Cpu.h>

#include <iostream>

Cpu::Cpu(std::shared_ptr<MemoryMap> mainMemory)
    : m_mainMemory(mainMemory) 
{
    m_programCounter = 0x0100;
}

void Cpu::Execute() {


    Byte opcode = m_mainMemory->Read(m_programCounter);

    std::cout << std::hex << "Program counter: " << m_programCounter << "\n";
    std::cout << std::hex << "Opcode: " << static_cast<int>(opcode) << "\n";
    
    switch(opcode) {
        case 0x00:
            NoOperation();
            m_programCounter++;
            break;

        case 0x01:
            LoadRegister(m_regC, m_mainMemory->Read(m_programCounter + 1));
            LoadRegister(m_regB, m_mainMemory->Read(m_programCounter + 2));
            m_programCounter += 3;
            break;

        case 0x02:
            {
            auto address = CombineRegisters(m_regB, m_regC);
            LoadRegister(m_regA, m_mainMemory->Read(address));
            m_programCounter++;
            break;
            }

        case 0x03:
            {
            auto bc = CombineRegisters(m_regB, m_regC);
            bc++;
            LoadRegister(m_regB, (bc >> 8) & 0xFFFF);
            LoadRegister(m_regC, bc & 0xFFFF);
            m_programCounter++;
            }
            break;
        
        case 0x04:
            Increment(m_regB);
            m_programCounter++;
            break;
        
        case 0x05:
            Decrement(m_regB);
            m_programCounter++;
            break;

        case 0x06:
            LoadRegister(m_regB, m_mainMemory->Read(m_programCounter+1));
            m_programCounter += 2;
            break;
        
        case 0x07:
            UnimplementedOperation("RLCA");
            m_programCounter++;
            break;

        case 0x08:
            UnimplementedOperation("LD (a16), SP");
            m_programCounter++;
            break;

        case 0x09:
            UnimplementedOperation("ADD HL, BC");
            m_programCounter++;
            break;

        case 0x0A:
            {
            auto address = CombineRegisters(m_regB, m_regC);
            LoadRegister(m_regA, m_mainMemory->Read(address));            
            m_programCounter++;
            break;
            }

        case 0x0B:
            UnimplementedOperation("DEC BC");
            m_programCounter++;
            break;
        
        case 0x0C:
            Increment(m_regC);
            m_programCounter++;
            break;
        
        case 0x0D:
            Decrement(m_regC);
            m_programCounter++;
            break;
        
        case 0x0E:
            LoadRegister(m_regC, m_mainMemory->Read(m_programCounter +1));
            m_programCounter += 2;
            break;
        
        case 0x0F:
            UnimplementedOperation("RRCA");
            m_programCounter++;
            break;
        
        case 0x10:
            UnimplementedOperation("STOP");
            m_programCounter++;
            break;

        case 0x11:
            UnimplementedOperation("LD DE, d16");
            m_programCounter++;
            break;
        
        case 0x12:
            {
            auto address = CombineRegisters(m_regD, m_regE);
            m_mainMemory->Write(address, m_regA);
            m_programCounter++;
            break;
            }
        
        case 0x13:
            UnimplementedOperation("INC DE");
            m_programCounter++;
            break;
        
        case 0x14:
            Increment(m_regD);
            m_programCounter++;
            break;
        
        case 0x15:
            Decrement(m_regD);
            m_programCounter++;
            break;
        
        case 0x16:
            LoadRegister(m_regD, m_mainMemory->Read(m_programCounter +1));
            m_programCounter += 2;
            break;
        
        case 0x17:
            UnimplementedOperation("RLA");
            m_programCounter++;
            break;

        case 0x18:
            {
                auto r8 = m_mainMemory->Read(m_programCounter + 1);
                m_programCounter += r8;
            }
            break;
        
        case 0x19:
            UnimplementedOperation("ADD, HL, DE");
            m_programCounter++;
            break;
        
        case 0x1A:
            {
            auto address = CombineRegisters(m_regD, m_regE);
            LoadRegister(m_regA, m_mainMemory->Read(address));
            m_programCounter++;
            break;
            }
        
        case 0x1B:
            UnimplementedOperation("DEC DE");
            m_programCounter++;
            break;
        
        case 0x1C:
            Increment(m_regE);
            m_programCounter++;
            break;

        case 0x1D:
            Decrement(m_regE);
            m_programCounter++;
            break;
        
        case 0x1E:
            LoadRegister(m_regE, m_mainMemory->Read(m_programCounter + 1));
            m_programCounter += 2;
            break;
        
        case 0x1F:
            UnimplementedOperation("RRA");
            m_programCounter++;
            break;

        case 0x20:
            UnimplementedOperation("JR NZ, r8");
            m_programCounter++;
            break;
        
        case 0x21:
            UnimplementedOperation("LD HL, d16");
            m_programCounter++;
            break;
        
        case 0x22:
            UnimplementedOperation("LD (HL+), A");
            m_programCounter++;
            break;
        
        case 0x23:
            UnimplementedOperation("INC HL");
            m_programCounter++;
            break;

        case 0x24:
            Increment(m_regH);
            m_programCounter++;
            break;
        
        case 0x25:
            Decrement(m_regH);
            m_programCounter++;
            break;
        
        case 0x26:
            LoadRegister(m_regH, m_mainMemory->Read(m_programCounter+1));
            m_programCounter += 2;
            break;
        
        case 0x27:
            UnimplementedOperation("DAA");
            m_programCounter++;
            break;
        
        case 0x28:
            {
            if (m_regF.test(7)) {
                int8_t r8 = m_mainMemory->Read(m_programCounter + 1);
                std::cout << "Jump relative:" << (int) r8 << "\n";
                std::cout << "Address: " << m_programCounter << "\n";
                m_programCounter += r8;
            } else {
                m_programCounter++;
            }
            break;
            }

        case 0x29:
            UnimplementedOperation("ADD HL, HL");
            m_programCounter++;
            break;
        
        case 0x2A:
            UnimplementedOperation("LD A, (HL+)");
            m_programCounter++;
            break;
        
        case 0x2B:
            UnimplementedOperation("DEC HL");
            m_programCounter++;
            break;
        
        case 0x2C:
            Increment(m_regL);
            m_programCounter++;
            break;
        
        case 0x2D:
            Decrement(m_regL);
            m_programCounter++;
            break;
        
        case 0x2E:
            LoadRegister(m_regL, m_mainMemory->Read(m_programCounter += 1));
            m_programCounter += 2;
            break;
        
        case 0x2F:
            UnimplementedOperation("CPL");
            m_programCounter++;
            break;
        
        case 0x30:
            UnimplementedOperation("JR NZ, r8");
            m_programCounter++;
            break;
        
        case 0x31:
            UnimplementedOperation("LD SP, d16");
            m_programCounter++;
            break;
        
        case 0x32:
            UnimplementedOperation("LD (HL+), A");
            m_programCounter++;
            break;
        
        case 0x33:
            m_stackPtr++;
            m_programCounter++;
            break;
        
        case 0x34:
            UnimplementedOperation("INC HL");
            m_programCounter++;
            break;
        
        case 0x35:
            UnimplementedOperation("DEC HL");
            m_programCounter++;
            break;
        
        case 0x36:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            m_mainMemory->Write(address, m_mainMemory->Read(m_programCounter + 1));
            m_programCounter += 2;
            break;
            }
        
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
            m_stackPtr--;
            m_programCounter++;
            break;
        
        case 0x3C:
            Increment(m_regA);
            m_programCounter++;
            break;
        
        case 0x3D:
            Decrement(m_regA);
            m_programCounter++;
            break;
        
        case 0x3E: 
            LoadRegister(m_regA, m_mainMemory->Read(m_programCounter + 1));
            m_programCounter += 2;
            break;

        case 0x3F:
            UnimplementedOperation("CCF");
            break;
        
        case 0x40:
            LoadRegister(m_regB, m_regB);
            m_programCounter++;
            break;
        
        case 0x41:
            LoadRegister(m_regB, m_regC);
            m_programCounter++;
            break;
        
        case 0x42:
            LoadRegister(m_regB, m_regD);
            m_programCounter++;
            break;
        
        case 0x43:
            LoadRegister(m_regB, m_regE);
            m_programCounter++;
            break;
        
        case 0x44:
            LoadRegister(m_regB, m_regH);
            m_programCounter++;
            break;
        
        case 0x45:
            LoadRegister(m_regB, m_regL);
            m_programCounter++;
            break;
        
        case 0x46:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            LoadRegister(m_regB, m_mainMemory->Read(address));
            m_programCounter++;
            break;
            }
        
        case 0x47:
            LoadRegister(m_regB, m_regA);
            m_programCounter++;
            break;
        
        case 0x48:
            LoadRegister(m_regC, m_regB);
            m_programCounter++;
            break;
        
        case 0x49:
            LoadRegister(m_regC, m_regC);
            m_programCounter++;
            break;
        
        case 0x4A:
            LoadRegister(m_regC, m_regD);
            m_programCounter++;
            break;
        
        case 0x4B:
            LoadRegister(m_regC, m_regE);
            m_programCounter++;
            break;
        
        case 0x4C:
            LoadRegister(m_regC, m_regH);
            m_programCounter++;
            break;
        
        case 0x4D:
            LoadRegister(m_regC, m_regL);
            m_programCounter++;
            break;
        
        case 0x4E:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            LoadRegister(m_regC, m_mainMemory->Read(address));
            m_programCounter++;
            break;
            }
        
        case 0x4F:
            LoadRegister(m_regC, m_regA);
            m_programCounter++;
            break;

        case 0x50:
            LoadRegister(m_regD, m_regB);
            m_programCounter++;
            break;

        case 0x51:
            LoadRegister(m_regD, m_regC);
            m_programCounter++;
            break;

        case 0x52:
            LoadRegister(m_regD, m_regD);
            m_programCounter++;
            break;

        case 0x53:
            LoadRegister(m_regD, m_regE);
            m_programCounter++;
            break;

        case 0x54:
            LoadRegister(m_regD, m_regH);
            m_programCounter++;
            break;

        case 0x55:
            LoadRegister(m_regD, m_regL);
            m_programCounter++;
            break;

        case 0x56:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            LoadRegister(m_regD, m_mainMemory->Read(address));
            m_programCounter++;
            break;
            }

        case 0x57:
            LoadRegister(m_regD, m_regA);
            m_programCounter++;
            break;

        case 0x58:
            LoadRegister(m_regE, m_regB);
            m_programCounter++;
            break;

        case 0x59:
            LoadRegister(m_regE, m_regC);
            m_programCounter++;
            break;

        case 0x5A:
            LoadRegister(m_regE, m_regD);
            m_programCounter++;
            break;

        case 0x5B:
            LoadRegister(m_regE, m_regE);
            m_programCounter++;
            break;

        case 0x5C:
            LoadRegister(m_regE, m_regH);
            m_programCounter++;
            break;

        case 0x5D:
            LoadRegister(m_regE, m_regL);
            m_programCounter++;
            break;

        case 0x5E:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            LoadRegister(m_regE, m_mainMemory->Read(address));
            m_programCounter++;
            break;
            }

        case 0x5F:
            LoadRegister(m_regE, m_regA);
            m_programCounter++;
            break;

        case 0x60:
            LoadRegister(m_regH, m_regB);
            m_programCounter++;
            break;

        case 0x61:
            LoadRegister(m_regH, m_regC);
            m_programCounter++;
            break;

        case 0x62:
            LoadRegister(m_regH, m_regD);
            m_programCounter++;
            break;

        case 0x63:
            LoadRegister(m_regH, m_regE);
            m_programCounter++;
            break;

        case 0x64:
            LoadRegister(m_regH, m_regH);
            m_programCounter++;
            break;

        case 0x65:
            LoadRegister(m_regH, m_regL);
            m_programCounter++;
            break;

        case 0x66:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            LoadRegister(m_regH, m_mainMemory->Read(address));
            m_programCounter++;
            break;
            }

        case 0x67:
            LoadRegister(m_regH, m_regA);
            m_programCounter++;
            break;

        case 0x68: 
            LoadRegister(m_regL, m_regB);
            m_programCounter++;
            break;
        
        case 0x69:
            LoadRegister(m_regL, m_regC);
            m_programCounter++;
            break;
        
        case 0x6A:
            LoadRegister(m_regL, m_regD);
            m_programCounter++;
            break;
        
        case 0x6B:
            LoadRegister(m_regL, m_regE);
            m_programCounter++;
            break;
        
        case 0x6C:
            LoadRegister(m_regL, m_regH);
            m_programCounter++;
            break;
        
        case 0x6D:
            LoadRegister(m_regL, m_regL);
            m_programCounter++;
            break;
        
        case 0x6E:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            LoadRegister(m_regL, m_mainMemory->Read(address));
            m_programCounter++;
            break;
            }
        
        case 0x6F:
            LoadRegister(m_regL, m_regA);
            m_programCounter++;
            break;
        
        case 0x70:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            m_mainMemory->Write(address, m_regB);
            m_programCounter++;
            break;
            }

        case 0x71:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            m_mainMemory->Write(address, m_regC);
            m_programCounter++;
            break;
            }

        case 0x72:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            m_mainMemory->Write(address, m_regD);            
            m_programCounter++;
            break;
            }
        
        case 0x73: 
            {
            auto address = CombineRegisters(m_regH, m_regL);
            m_mainMemory->Write(address, m_regE);
            m_programCounter++;
            break;
            }
        
        case 0x74:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            m_mainMemory->Write(address, m_regH);
            m_programCounter++;
            break;
            }
        
        case 0x75:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            m_mainMemory->Write(address, m_regL);
            m_programCounter++;
            break;
            }
        
        case 0x76:
            UnimplementedOperation("HALT");
            m_programCounter++;
            break;
        

        case 0x77:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            m_mainMemory->Write(address, m_regL);
            m_programCounter++;
            break;
            }

        case 0x78:
            LoadRegister(m_regA, m_regB);
            m_programCounter++;
            break;
        
        case 0x79:
            LoadRegister(m_regA, m_regC);
            m_programCounter++;
            break;
        
        case 0x7A:
            LoadRegister(m_regA, m_regD);
            m_programCounter++;
            break;
        
        case 0x7B:
            LoadRegister(m_regA, m_regE);
            m_programCounter++;
            break;
        
        case 0x7C:
            LoadRegister(m_regA, m_regH);
            m_programCounter++;
            break;
        
        case 0x7D:
            LoadRegister(m_regA, m_regL);
            m_programCounter++;
            break;
        
        case 0x7E:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            LoadRegister(m_regA, m_mainMemory->Read(address));
            m_programCounter++;
            break;
            }
        
        case 0x7F:
            LoadRegister(m_regA, m_regA);
            m_programCounter++;
            break;
        
        case 0x80:
            AddRegisters(m_regA, m_regB);
            m_programCounter++;
            break;
        
        case 0x81:
            AddRegisters(m_regA, m_regC);
            m_programCounter++;
            break;
        
        case 0x82:
            AddRegisters(m_regA, m_regD);
            m_programCounter++;
            break;

        case 0x83:
            AddRegisters(m_regA, m_regE);
            m_programCounter++;
            break;
        
        case 0x84:
            AddRegisters(m_regA, m_regH);
            m_programCounter++;
            break;
        
        case 0x85:
            AddRegisters(m_regA, m_regL);
            m_programCounter++;
            break;
        
        case 0x86:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            AddRegisters(m_regA, m_mainMemory->Read(address));
            m_programCounter++;
            break;
            }

        case 0x87:
            AddRegisters(m_regA, m_regA);
            m_programCounter++;
            break;

        case 0x88:
            UnimplementedOperation("ADC A, B");
            m_programCounter++;
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
            AndWithA(m_regB);
            m_programCounter++;
            break;
        
        case 0xA1:
            AndWithA(m_regC);
            m_programCounter++;
            break;
        
        case 0xA2:
            AndWithA(m_regD);
            m_programCounter++;
            break;
        
        case 0xA3:
            AndWithA(m_regE);
            m_programCounter++;
            break;
        
        case 0xA4:
            AndWithA(m_regH);
            m_programCounter++;
            break;
        
        case 0xA5:
            AndWithA(m_regL);
            m_programCounter++;
            break;
        
        case 0xA6:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            AndWithA(m_mainMemory->Read(address));
            m_programCounter++;
            break;
            }

        case 0xA7:
            AndWithA(m_regA);
            m_programCounter++;
            break;
        
        case 0xA8:
            XorWithA(m_regB);
            m_programCounter++;
            break;
        
        case 0xA9:
            XorWithA(m_regC);
            m_programCounter++;
            break;
        
        case 0xAA:
            XorWithA(m_regD);
            m_programCounter++;
            break;
        
        case 0xAB:
            XorWithA(m_regE);
            m_programCounter++;
            break;
        
        case 0xAC:
            XorWithA(m_regH);
            m_programCounter++;
            break;
        
        case 0xAD:
            XorWithA(m_regL);
            m_programCounter++;
            break;
        
        case 0xAE:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            XorWithA(m_mainMemory->Read(address));
            m_programCounter++;
            break;
            }
        
        case 0xAF:
            XorWithA(m_regA);
            m_programCounter++;
            break;
        
        case 0xB0:
            OrWithA(m_regB);
            m_programCounter++;
            break;
        
        case 0xB1:
            OrWithA(m_regC);
            m_programCounter++;
            break;
        
        case 0xB2:
            OrWithA(m_regD);
            m_programCounter++;
            break;
        
        case 0xB3:
            OrWithA(m_regE);
            m_programCounter++;
            break;
        
        case 0xB4:
            OrWithA(m_regH);
            m_programCounter++;
            break;
        
        case 0xB5:
            OrWithA(m_regL);
            m_programCounter++;
            break;
        
        case 0xB6:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            OrWithA(m_mainMemory->Read(address));
            m_programCounter++;
            break;
            }

        case 0xB7:
            OrWithA(m_regA);
            m_programCounter++;
            break;
        
        case 0xB8:
            CompareWithA(m_regB);
            m_programCounter++;
            break;
        
        case 0xB9:
            CompareWithA(m_regC);
            m_programCounter++;
            break;
        
        case 0xBA:
            CompareWithA(m_regD);
            m_programCounter++;
            break;
        
        case 0xBB:
            CompareWithA(m_regE);
            m_programCounter++;
            break;
        
        case 0xBC:
            CompareWithA(m_regH);
            m_programCounter++;
            break;
        
        case 0xBD:
            CompareWithA(m_regL);
            m_programCounter++;
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
            {
            auto address = CombineRegisters(m_mainMemory->Read(m_programCounter+2), m_mainMemory->Read(m_programCounter+1));
            std::cout << "Address: " << address << "\n";
            m_programCounter = address;
            break;
            }
        
        case 0xC4:
            UnimplementedOperation("CALL NZ, a16");
            break;
        
        case 0xC5:
            UnimplementedOperation("PUSH BC");
            break;
        
        case 0xC6:
            AddRegisters(m_regA, m_mainMemory->Read(m_programCounter + 1));
            m_programCounter += 2;
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
            {
                uint16_t address = 0xFF00 + m_mainMemory->Read(m_programCounter + 1);
                m_mainMemory->Write(address, m_regA);
                m_programCounter += 2;
            }
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
            AndWithA(m_mainMemory->Read(m_programCounter + 1));
            m_programCounter += 2;
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
            {
            auto address = CombineRegisters(m_mainMemory->Read(m_programCounter + 2), m_mainMemory->Read(m_programCounter +1));
            m_mainMemory->Write(address, m_regA);
            m_programCounter += 3;
            break;
            }

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
            XorWithA(m_mainMemory->Read(m_programCounter + 1));
            m_programCounter += 2;
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
            DisableInterrupts();
            m_programCounter++;
            break;
        
        case 0xF4:
            UnimplementedOperation("Unsupported opcode");
            break;
        
        case 0xF5:
            UnimplementedOperation("PUSH AF");
            break;
        
        case 0xF6:
            OrWithA(m_mainMemory->Read(m_programCounter + 1));
            m_programCounter += 2;
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
            CompareWithA(m_mainMemory->Read(m_programCounter+1));
            m_programCounter += 2;
            break;
        
        case 0xFF:
            UnimplementedOperation("RST 38H");
            break;

        default:
            UnimplementedOperation("Invalid Opcode");
    }

}

void Cpu::NoOperation() {
    return;
}

void Cpu::LoadRegister(Byte& to, const Byte& from) {
    to = from;
}

void Cpu::Increment(Byte& reg) {
    reg++;

    if (reg == 0) {
        m_regF.set(7);
    }

    m_regF.reset(6);
    
    //Set H if carry from bit 3
}

void Cpu::Decrement(Byte& reg) {
    reg--;

    if (reg == 0) {
        m_regF.set(7);
    }

    m_regF.set(6);
    // Set if no borrow from bit 4

}

uint16_t Cpu::CombineRegisters(const Byte& high, const Byte& low) const {

    uint16_t combinedRegister = (high << 8) | low;

    return combinedRegister;
}

void Cpu::AddRegisters(Byte& to, const Byte& from) {

    to += from;

    //flags;
}

void Cpu::SubtractRegister(Byte& to, const Byte& from) {

    to -= from;
}

void Cpu::UnimplementedOperation(const std::string& operation) {
    std::cerr << "Unimplemented operation: \t" << operation << "\n";
}

void Cpu::AndWithA(const Byte& reg) {
    m_regA &= reg;

    if (m_regA == 0) {
        m_regF.set(7);
    }

    m_regF.reset(6);
    m_regF.set(5);
    m_regF.reset(4);
}

void Cpu::OrWithA(const Byte& reg) {
    m_regA |= reg;

    if (m_regA == 0) {
        m_regF.set(7);
    }

    m_regF.reset(6);
    m_regF.reset(5);
    m_regF.reset(4);
}

void Cpu::XorWithA(const Byte& reg) {
    m_regA ^= reg;

    if (m_regA == 0) {
        m_regF.set(7);
    }

    m_regF.reset(6);
    m_regF.reset(5);
    m_regF.reset(4);
}

void Cpu::CompareWithA(const Byte& reg) {

    if(m_regA == reg) {
        m_regF.set(7);
    }

    m_regF.set(6);

    //Set H if no borrow from bit 4

    if(m_regA < reg) {
        m_regF.set(4);
    }
}

void Cpu::DisableInterrupts() {

}
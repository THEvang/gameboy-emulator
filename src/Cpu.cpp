#include <Cpu.h>

#include <iostream>

Cpu::Cpu(std::shared_ptr<MemoryMap> mainMemory)
    : m_mainMemory(mainMemory) 
{
    SetInitialState();
}

void Cpu::SetInitialState() {
    m_programCounter = 0x0100;
    m_stackPtr = 0xFFFE;

    m_regA = 0x01;
    m_regF = std::bitset<8>(0xB0);
    m_regB = 0x00;
    m_regC = 0x13;
    m_regD = 0x00;
    m_regE = 0xD8;
    m_regH = 0x01;
    m_regL = 0x4D;

    m_mainMemory->Write(0xFF05, 0x00);
    m_mainMemory->Write(0xFF06, 0x00);
    m_mainMemory->Write(0xFF07, 0x00);

    m_mainMemory->Write(0xFF10, 0x80);
    m_mainMemory->Write(0xFF11, 0xBF);
    m_mainMemory->Write(0xFF12, 0xF3);

    m_mainMemory->Write(0xFF14, 0xBF);

    m_mainMemory->Write(0xFF16, 0x3F);
    m_mainMemory->Write(0xFF17, 0x00);
    
    m_mainMemory->Write(0xFF19, 0xBF);
    m_mainMemory->Write(0xFF1A, 0x7F);
    m_mainMemory->Write(0xFF1B, 0xFF);
    m_mainMemory->Write(0xFF1C, 0x9F);
    m_mainMemory->Write(0xFF1E, 0xBF);
    m_mainMemory->Write(0xFF20, 0xFF);
    m_mainMemory->Write(0xFF21, 0x00);
    m_mainMemory->Write(0xFF22, 0x00);

    m_mainMemory->Write(0xFF23, 0xBF);
    m_mainMemory->Write(0xFF24, 0x77);
    m_mainMemory->Write(0xFF25, 0xF3);
    m_mainMemory->Write(0xFF26, 0xF1);
    m_mainMemory->Write(0xFF40, 0x91);
    m_mainMemory->Write(0xFF42, 0x00);
    m_mainMemory->Write(0xFF43, 0x00);

    m_mainMemory->Write(0xFF45, 0x00);
    m_mainMemory->Write(0xFF47, 0xFC);
    m_mainMemory->Write(0xFF48, 0xFF);
    m_mainMemory->Write(0xFF49, 0xFF);
    m_mainMemory->Write(0xFF4A, 0x00);
    m_mainMemory->Write(0xFF4B, 0x00);
    m_mainMemory->Write(0xFFFF, 0x00);
}

void Cpu::Execute() {

    Byte opcode = m_mainMemory->Read(m_programCounter);

    std::cout << std::hex << "Program counter: " << m_programCounter << "\n";
    std::cout << std::hex << "Opcode: " << static_cast<int>(opcode) << "\n";

    std::cout << std::hex << "Register A: \t" << static_cast<int>(m_regA) << "\n";
    std::cout << std::hex << "Register B: \t" << static_cast<int>(m_regB) << "\n";
    std::cout << std::hex << "Register C: \t" << static_cast<int>(m_regC) << "\n";
    std::cout << std::hex << "Register D: \t" << static_cast<int>(m_regD) << "\n";
    std::cout << std::hex << "Register E: \t" << static_cast<int>(m_regE) << "\n";
    std::cout << std::hex << "Register H: \t" << static_cast<int>(m_regH) << "\n";
    std::cout << std::hex << "Register L: \t" << static_cast<int>(m_regL) << "\n";

    std::cout << "\n";
    std::cout << std::hex << "SC: " << static_cast<int>(m_mainMemory->Read(0xFF02)) << "\n";

    //if(m_mainMemory->Read(0xFF02) == 0x81) {
        std::cout << "SB: ";
        std::cout  <<  static_cast<int>(m_mainMemory->Read(0xFF01)) << "\n";
    //}
    
    switch(opcode) {
        case 0x00:
            NoOperation();
            break;

        case 0x01:
            LoadImmediate16BitValue(m_regB, m_regC);
            break;

        case 0x02:
            LoadToAddress(CombineRegisters(m_regB, m_regC), m_regA);
            break;

        case 0x03:
            IncrementRegisterPair(m_regB, m_regC);
            break;
        
        case 0x04:
            IncrementRegister(m_regB);
            break;
        
        case 0x05:
            DecrementRegister(m_regB);
            break;

        case 0x06:
            LoadFromImmediateByte(m_regB);
            break;
        
        case 0x07:
            RLCA();
            break;

        case 0x08:
            UnimplementedOperation("LD (a16), SP");
            m_programCounter += 3;
            break;

        case 0x09:
            UnimplementedOperation("ADD HL, BC");
            m_programCounter++;
            break;

        case 0x0A:
            LoadFromAddress(m_regA, CombineRegisters(m_regB, m_regC));
            break;

        case 0x0B:
            DecrementRegisterPair(m_regB, m_regC);
            break;
        
        case 0x0C:
            IncrementRegister(m_regC);
            break;
        
        case 0x0D:
            DecrementRegister(m_regC);
            break;
        
        case 0x0E:
            LoadFromImmediateByte(m_regC);
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
            LoadImmediate16BitValue(m_regD, m_regE);
            break;
        
        case 0x12:
            LoadToAddress(CombineRegisters(m_regD, m_regE), m_regA);
            break;
        
        case 0x13:
            IncrementRegisterPair(m_regD, m_regE);
            break;
        
        case 0x14:
            IncrementRegister(m_regD);
            break;
        
        case 0x15:
            DecrementRegister(m_regD);
            break;
        
        case 0x16:
            LoadFromImmediateByte(m_regD);
            break;
        
        case 0x17:
            UnimplementedOperation("RLA");
            m_programCounter++;
            break;

        case 0x18:
            JumpRelative();
            break;
        
        case 0x19:
            UnimplementedOperation("ADD, HL, DE");
            m_programCounter++;
            break;
        
        case 0x1A:
            LoadFromAddress(m_regA, CombineRegisters(m_regD, m_regE));
            break;
        
        case 0x1B:
            DecrementRegisterPair(m_regD, m_regE);
            break;
        
        case 0x1C:
            IncrementRegister(m_regE);
            break;

        case 0x1D:
            DecrementRegister(m_regE);
            break;
        
        case 0x1E:
            LoadFromImmediateByte(m_regE);
            break;
        
        case 0x1F:
            RR(m_regA);
            break;

        case 0x20:
            JumpRelativeNZ();
            break;
        
        case 0x21:
            LoadImmediate16BitValue(m_regH, m_regL);
            break;
        
        case 0x22:
            LDIHL();
            break;
        
        case 0x23:
            IncrementRegisterPair(m_regH, m_regL);
            break;

        case 0x24:
            IncrementRegister(m_regH);
            break;
        
        case 0x25:
            DecrementRegister(m_regH);
            break;
        
        case 0x26:
            LoadFromImmediateByte(m_regH);
            break;
        
        case 0x27:
            UnimplementedOperation("DAA");
            m_programCounter++;
            break;
        
        case 0x28:
            JumpRelativeZ();
            break;

        case 0x29:
            UnimplementedOperation("ADD HL, HL");
            m_programCounter++;
            break;
        
        case 0x2A:
            LDIA();
            break;
        
        case 0x2B:
            DecrementRegisterPair(m_regH, m_regL);
            break;
        
        case 0x2C:
            IncrementRegister(m_regL);
            break;
        
        case 0x2D:
            DecrementRegister(m_regL);
            break;
        
        case 0x2E:
            LoadFromImmediateByte(m_regL);
            break;
        
        case 0x2F:
            ComplementA();
            break;
        
        case 0x30:
            JumpRelativeNC();
            break;
        
        case 0x31:
            LoadImmediate16BitValue(m_stackPtr);
            break;
        
        case 0x32:
            UnimplementedOperation("LD (HL+), A");
            m_programCounter++;
            break;
        
        case 0x33:
            IncrementStackpointer();
            break;
        
        case 0x34:
            IncrementAtAddress(CombineRegisters(m_regH, m_regL));
            break;
        
        case 0x35:
            DecrementAtAddress(CombineRegisters(m_regH, m_regL));
            break;
        
        case 0x36:
            {
            auto address = CombineRegisters(m_regH, m_regL);
            m_mainMemory->Write(address, m_mainMemory->Read(m_programCounter + 1));
            m_programCounter += 2;
            break;
            }
        
        case 0x37:
            SetCarryFlag();
            break;
        
        case 0x38:
            JumpRelativeC();
            break;
        
        case 0x39:
            UnimplementedOperation("ADD HL, SP");
            break;
        
        case 0x3A:
            UnimplementedOperation("LD A, (HL-)");
            break;
        
        case 0x3B:
            DecrementStackPointer();
            break;
        
        case 0x3C:
            IncrementRegister(m_regA);
            break;
        
        case 0x3D:
            DecrementRegister(m_regA);
            break;
        
        case 0x3E:
            LoadFromImmediateByte(m_regA);
            break;

        case 0x3F:
            ComplementCarryFlag();
            break;
        
        case 0x40:
            LoadFromRegister(m_regB, m_regB);
            break;
        
        case 0x41:
            LoadFromRegister(m_regB, m_regC);
            break;
        
        case 0x42:
            LoadFromRegister(m_regB, m_regD);
            break;
        
        case 0x43:
            LoadFromRegister(m_regB, m_regE);
            break;
        
        case 0x44:
            LoadFromRegister(m_regB, m_regH);
            break;
        
        case 0x45:
            LoadFromRegister(m_regB, m_regL);
            break;
        
        case 0x46:
            LoadFromAddress(m_regB, CombineRegisters(m_regH, m_regL));
            break;
        
        case 0x47:
            LoadFromRegister(m_regB, m_regA);
            break;
        
        case 0x48:
            LoadFromRegister(m_regC, m_regB);
            break;
        
        case 0x49:
            LoadFromRegister(m_regC, m_regC);
            break;
        
        case 0x4A:
            LoadFromRegister(m_regC, m_regD);
            break;
        
        case 0x4B:
            LoadFromRegister(m_regC, m_regE);
            break;
        
        case 0x4C:
            LoadFromRegister(m_regC, m_regH);
            break;
        
        case 0x4D:
            LoadFromRegister(m_regC, m_regL);
            break;
        
        case 0x4E:
            LoadFromAddress(m_regC, CombineRegisters(m_regH, m_regL));
            break;
        
        case 0x4F:
            LoadFromRegister(m_regC, m_regA);
            break;

        case 0x50:
            LoadFromRegister(m_regD, m_regB);
            break;

        case 0x51:
            LoadFromRegister(m_regD, m_regC);
            break;

        case 0x52:
            LoadFromRegister(m_regD, m_regD);
            break;

        case 0x53:
            LoadFromRegister(m_regD, m_regE);
            break;

        case 0x54:
            LoadFromRegister(m_regD, m_regH);
            break;

        case 0x55:
            LoadFromRegister(m_regD, m_regL);
            break;

        case 0x56:
            LoadFromAddress(m_regD, CombineRegisters(m_regH, m_regL));
            break;

        case 0x57:
            LoadFromRegister(m_regD, m_regA);
            break;

        case 0x58:
            LoadFromAddress(m_regE, m_regB);
            break;

        case 0x59:
            LoadFromRegister(m_regE, m_regC);
            break;

        case 0x5A:
            LoadFromRegister(m_regE, m_regD);
            break;

        case 0x5B:
            LoadFromRegister(m_regE, m_regE);
            break;

        case 0x5C:
            LoadFromRegister(m_regE, m_regH);
            break;

        case 0x5D:
            LoadFromRegister(m_regE, m_regL);
            break;

        case 0x5E:
            LoadFromAddress(m_regE, CombineRegisters(m_regH, m_regL));
            break;

        case 0x5F:
            LoadFromRegister(m_regE, m_regA);
            break;

        case 0x60:
            LoadFromRegister(m_regH, m_regB);
            break;

        case 0x61:
            LoadFromRegister(m_regH, m_regC);
            break;

        case 0x62:
            LoadFromRegister(m_regH, m_regD);
            break;

        case 0x63:
            LoadFromRegister(m_regH, m_regE);
            break;

        case 0x64:
            LoadFromRegister(m_regH, m_regH);
            break;

        case 0x65:
            LoadFromRegister(m_regH, m_regL);
            break;

        case 0x66:
            LoadFromAddress(m_regH, CombineRegisters(m_regH, m_regL));
            break;

        case 0x67:
            LoadFromRegister(m_regH, m_regA);
            break;

        case 0x68: 
            LoadFromRegister(m_regL, m_regB);
            break;
        
        case 0x69:
            LoadFromRegister(m_regL, m_regC);
            break;
        
        case 0x6A:
            LoadFromRegister(m_regL, m_regD);
            break;
        
        case 0x6B:
            LoadFromRegister(m_regL, m_regE);
            break;
        
        case 0x6C:
            LoadFromRegister(m_regL, m_regH);
            break;
        
        case 0x6D:
            LoadFromRegister(m_regL, m_regL);
            break;
        
        case 0x6E:
            LoadFromAddress(m_regL, CombineRegisters(m_regH, m_regL));
            break;
        
        case 0x6F:
            LoadFromRegister(m_regL, m_regA);
            break;
        
        case 0x70:
            LoadToAddress(CombineRegisters(m_regH, m_regL), m_regB);
            break;

        case 0x71:
            LoadToAddress(CombineRegisters(m_regH, m_regL), m_regC);
            break;

        case 0x72:
            LoadToAddress(CombineRegisters(m_regH, m_regL), m_regD);
            break;
        
        case 0x73:
            LoadToAddress(CombineRegisters(m_regH, m_regL), m_regE); 
            break;
        
        case 0x74:
            LoadToAddress(CombineRegisters(m_regH, m_regL), m_regH);
            break;
        
        case 0x75:
            LoadToAddress(CombineRegisters(m_regH, m_regL), m_regL);
            break;
        
        case 0x76:
            UnimplementedOperation("HALT");
            m_programCounter++;
            break;
        
        case 0x77:
            LoadToAddress(CombineRegisters(m_regH, m_regL), m_regA);
            break;

        case 0x78:
            LoadFromRegister(m_regA, m_regB);
            break;
        
        case 0x79:
            LoadFromRegister(m_regA, m_regC);
            break;
        
        case 0x7A:
            LoadFromRegister(m_regA, m_regD);
            break;
        
        case 0x7B:
            LoadFromRegister(m_regA, m_regE);
            break;
        
        case 0x7C:
            LoadFromRegister(m_regA, m_regH);
            break;
        
        case 0x7D:
            LoadFromRegister(m_regA, m_regL);
            break;
        
        case 0x7E:
            LoadFromAddress(m_regA, CombineRegisters(m_regH, m_regL));
            break;
        
        case 0x7F:
            LoadFromRegister(m_regA, m_regA);
            break;
        
        case 0x80:
            AddRegisters(m_regA, m_regB);
            break;
        
        case 0x81:
            AddRegisters(m_regA, m_regC);
            break;
        
        case 0x82:
            AddRegisters(m_regA, m_regD);
            break;

        case 0x83:
            AddRegisters(m_regA, m_regE);
            break;
        
        case 0x84:
            AddRegisters(m_regA, m_regH);
            break;
        
        case 0x85:
            AddRegisters(m_regA, m_regL);
            break;
        
        case 0x86:
            UnimplementedOperation("ADD A, (HL)");
            break;
            
        case 0x87:
            AddRegisters(m_regA, m_regA);
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
            SubtractFromA(m_regB);
            break;
        
        case 0x91:
            SubtractFromA(m_regC);
            break;
        
        case 0x92:
            SubtractFromA(m_regD);
            break;
        
        case 0x93:
            SubtractFromA(m_regE);
            break;
        
        case 0x94:
            SubtractFromA(m_regH);
            break;
        
        case 0x95:
            SubtractFromA(m_regL);
            break;
        
        case 0x96:
            UnimplementedOperation("SUB (HL)");
            break;
        
        case 0x97:
            SubtractFromA(m_regA);
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
            CompareWithA(m_regA);
            m_programCounter++;
            break;
        
        case 0xC0:
            RetNZ();
            break;
        
        case 0xC1:
            Pop(m_regB, m_regC);
            break;
        
        case 0xC2:
            UnimplementedOperation("JP NZ, a16");
            break;
        
        case 0xC3:
            Jump();
            break;
        
        case 0xC4:
            UnimplementedOperation("CALL NZ, a16");
            break;
        
        case 0xC5:
            Push(m_regB, m_regC);
            break;
        
        case 0xC6:
            UnimplementedOperation("ADD A, n");
            break;
        
        case 0xC7:
            Restart(0x00);
            break;
        
        case 0xC8:
            UnimplementedOperation("RET Z");
            break;
        
        case 0xC9:
            Ret();
            break;
        
        case 0xCA:
            UnimplementedOperation("JP Z, a16");
            break;
        
        case 0xCB:
            m_programCounter++;
            ExecuteCB();
            break;
        
        case 0xCC: 
            UnimplementedOperation("CALL Z, a16");
            break;
        
        case 0xCD:
            Call();
            break;
        
        case 0xCE:
            UnimplementedOperation("ADC A, d8");
            break;
        
        case 0xCF:
            Restart(0x08);
            break;
        
        case 0xD0:
            UnimplementedOperation("RET NC");
            break;
        
        case 0xD1:
            Pop(m_regD, m_regE);
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
            Push(m_regD, m_regE);
            break;
        
        case 0xD6:
            SubtractImmediateByte();
            break;
        
        case 0xD7:
            Restart(0x10);
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
            Restart(0x18);
            break;
        
        case 0xE0:
            {
                uint16_t address = 0xFF00 + m_mainMemory->Read(m_programCounter + 1);
                m_mainMemory->Write(address, m_regA);
                m_programCounter += 2;
            }
            break;
        
        case 0xE1:
            Pop(m_regH, m_regL);
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
            Push(m_regH, m_regL);
            break;
        
        case 0xE6:
            AndWithA(m_mainMemory->Read(m_programCounter + 1));
            m_programCounter += 2;
            break;
        
        case 0xE7:
            Restart(0x20);
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
            m_cycles += 16;
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
            Restart(0x28);
            break;
        
        case 0xF0:
            LDHAN();
            m_programCounter++;
            break;
        
        case 0xF1:
            Pop(m_regA, m_regF);
            break;
        
        case 0xF2:
            UnimplementedOperation("LD A, (C)");
            break;
        
        case 0xF3:
            DisableInterrupts();
            break;
        
        case 0xF4:
            UnimplementedOperation("Unsupported opcode");
            break;
        
        case 0xF5:
            Push(m_regA, m_regF);
            break;
        
        case 0xF6:
            OrWithA(m_mainMemory->Read(m_programCounter + 1));
            m_programCounter += 2;
            break;
        
        case 0xF7:
            Restart(0x30);
            break;
        
        case 0xF8:
            UnimplementedOperation("LD HL, SP+r8");
            break;
        
        case 0xF9:
            LoadStackPointerFromHL();
            break;
        
        case 0xFA:
            {
            auto address = CombineRegisters(m_programCounter + 2, m_programCounter + 1);
            m_regA = m_mainMemory->Read(address);
            m_programCounter += 3;
            }
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
            Restart(0x38);
            break;

        default:
            UnimplementedOperation("Invalid Opcode");
    }

}

void Cpu::NoOperation() {
    m_programCounter++;
    return;
}

void Cpu::LoadToRegister(Byte& to, const Byte& from) {
    to = from;
}

void Cpu::IncrementRegister(Byte& reg) {

    if ( (((reg & 0xf) + ( (reg + 1) &0xf)) & 0x10) == 0x10) {
        m_regF.set(5);
    }

    reg++;

    if (reg == 0) {
        m_regF.set(7);
    }

    m_regF.reset(6);
 
    m_programCounter++;
    m_cycles += 4;
}

void Cpu::DecrementRegister(Byte& reg) {
    reg--;

    if (reg == 0) {
        m_regF.set(7);
    }

    m_regF.set(6);
    // Set if no borrow from bit 4

    m_programCounter++;
    m_cycles += 4;
}

uint16_t Cpu::CombineRegisters(const Byte& high, const Byte& low) const {

    uint16_t combinedRegister = (high << 8) | low;

    return combinedRegister;
}

void Cpu::AddRegisters(Byte& to, const Byte& from) {

    if ( (((to & 0xf) + ( (from +1) &0xf)) & 0x10) == 0x10) {
        m_regF.set(5);
    } 

    if( (static_cast<int>(to) + static_cast<int>(from)) > 0xFF) {
        m_regF.set(4);
    }

    if(to == 0) {
        m_regF.set(7);
    }

    m_regF.reset(6);

    to += from;

    m_programCounter++;
    m_cycles += 4;
}

void Cpu::SubtractFromA(uint8_t value) {

    if (value > m_regA) {
        m_regF.set(4);
    }

    m_regA -= value;

    if(m_regA == 0) {
        m_regF.set(7);
    }

    m_regF.set(6);

    m_programCounter++;
    m_cycles += 8;
    //Check borrow from 4 bit

}

void Cpu::SubtractFromAddress(uint16_t address) {

    auto value = m_mainMemory->Read(address);    

    m_regA -= value;

    if(m_regA == 0) {
        m_regF.set(7);
    }

    m_regF.set(6);


    //H - set if no borrow from bit 4
    //C - set if no borrow

    m_cycles += 8;
    m_programCounter++;
}

void Cpu::SubtractImmediateByte() {
    auto value = m_mainMemory->Read(m_programCounter + 1);
    m_regA -= value;

    if(m_regA == 0) {
        m_regF.set(7);
    }

    m_regF.set(6);

    //H - set if no borrow from bit 4
    //C - set if no borrow

    m_programCounter += 2;
    m_cycles += 8;
}

void Cpu::UnimplementedOperation(const std::string& operation) {
    std::cerr << "Unimplemented operation: \t" << operation << "\n";
    std::cin.get();
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
    
    m_programCounter++;
}

 
 void Cpu::ComplementA() {

    m_regA = ~m_regA;

    m_regF.set(6);
    m_regF.set(5);

    m_programCounter++;
    m_cycles += 4;
 }

 void Cpu::ComplementCarryFlag() {

    m_regF.flip(4);

    m_regF.reset(6);
    m_regF.reset(5);

    m_programCounter++;
    m_cycles += 4;
 }

 void Cpu::SetCarryFlag() {
     
     m_regF.set(4);
     m_regF.reset(6);
     m_regF.reset(5);

     m_programCounter++;
     m_cycles += 4;
 }

 void Cpu::Call() {

    auto address = m_programCounter + 3;

    m_mainMemory->Write(m_stackPtr, address);
    m_mainMemory->Write(m_stackPtr - 1, (address >> 8));
    m_stackPtr -= 2;

    m_programCounter = CombineRegisters(m_mainMemory->Read(m_programCounter + 2), m_mainMemory->Read(m_programCounter + 1));
    
    m_cycles += 12;
 }


 void Cpu::Ret() {
     auto address = CombineRegisters(m_mainMemory->Read(m_stackPtr + 1), m_mainMemory->Read(m_stackPtr));
     m_stackPtr += 2;

     m_programCounter = address;
     m_cycles += 12;
 }

 void Cpu::ExecuteCB() {

     auto opcode = m_mainMemory->Read(m_programCounter);

     std::cout << std::hex << "Program counter: " << m_programCounter << "\n";
     std::cout << std::hex << "Opcode: " << static_cast<int>(opcode) << "\n";

     switch (opcode) {
         case 0x00:
            UnimplementedOperation("RLC B");
            break;
        
        case 0x01:
            UnimplementedOperation("RLC C");
            break;
        
        case 0x02:
            UnimplementedOperation("RLC D");
            break;
        
        case 0x03:
            UnimplementedOperation("RLC E");
            break;
        
        case 0x04:
            UnimplementedOperation("RLC H");
            break;
        
        case 0x05:
            UnimplementedOperation("RLC L");
            break;
        
        case 0x06:
            UnimplementedOperation("RLC (HL)");
            break;
        
        case 0x07:
            UnimplementedOperation("RLC A");
            break;
        
        case 0x08:
            UnimplementedOperation("RRC B");
            break;
        
        case 0x09:
            UnimplementedOperation("RRC C");
            break;
        
        case 0x0A:
            UnimplementedOperation("RRC D");
            break;
        
        case 0x0B:
            UnimplementedOperation("RRC E");
            break;
        
        case 0x0C:
            UnimplementedOperation("RRC H");
            break;
        
        case 0x0D:
            UnimplementedOperation("RRC L");
            break;
        
        case 0x0E:
            UnimplementedOperation("RRC (HL");
            break;
        
        case 0x0F:
            UnimplementedOperation("RRC A");
            break;
        
        case 0x19:
            RR(m_regC);
            break;
        
        case 0x1A:
            RR(m_regD);
            break;

        case 0x38:
            SRL(m_regB);
            break;

        
        case 0xB7:
            m_regA &= ~(1ul << 6);
            m_programCounter++;
            break;
        
        default:
            UnimplementedOperation("Unavailable Opcode\n");
            break;
     }

 }

void Cpu::JumpRelativeNZ() {
    if (!m_regF.test(7)) {
        m_programCounter += static_cast<int8_t>(m_mainMemory->Read(m_programCounter + 1));
    } else {
        m_programCounter += 2;
    }

    m_cycles += 8;
}

void Cpu::JumpRelativeNC() {
    if (!m_regF.test(4)) {
        m_programCounter += static_cast<int8_t>(m_mainMemory->Read(m_programCounter + 1));
    } else {
        m_programCounter += 2;
    }

    m_cycles += 8;
}

void Cpu::JumpRelativeC() {
    if (m_regF.test(4)) {
        m_programCounter += static_cast<int8_t>(m_mainMemory->Read(m_programCounter + 1));
    } else {
        m_programCounter += 2;
    }

    m_cycles += 8;
}

void Cpu::Pop(uint8_t& high, uint8_t& low) {
    high = m_mainMemory->Read(m_stackPtr + 1);
    low = m_mainMemory->Read(m_stackPtr);

    m_stackPtr += 2;
    m_programCounter++;
}

void Cpu::Restart(uint8_t address) {
    m_mainMemory->Write(m_stackPtr, m_programCounter);
    m_stackPtr--;

    m_programCounter += 0x000 + address;
    m_cycles += 32;
}

void Cpu::LDHAN() {
    auto address = +0xFF00 + m_mainMemory->Read(m_programCounter + 1);

    m_regA = m_mainMemory->Read(address);

    m_programCounter++;
}

void Cpu::Push(uint8_t high, uint8_t low) {
    m_mainMemory->Write(m_stackPtr, high);
    m_stackPtr--;

    m_mainMemory->Write(m_stackPtr, low);
    m_stackPtr--;

    m_programCounter++;
}

void Cpu::Push(uint8_t high, std::bitset<8> low) {

    uint8_t lowBit = low.to_ulong();
    Push(high, lowBit);
}

void Cpu::LoadFromImmediateByte(uint8_t& to) {
    to = m_mainMemory->Read(m_programCounter + 1);

    m_programCounter += 2;
    m_cycles += 8;
}

void Cpu::LoadFromRegister(uint8_t& to, uint8_t from) {
    to = from;

    m_programCounter++;
    m_cycles += 4;
}


void Cpu::LoadFromAddress(Byte& to, uint16_t address) {
    to = m_mainMemory->Read(address);
    
    m_programCounter++;
    m_cycles += 8;
}

void Cpu::LoadToAddress(uint16_t address, uint8_t value) {
    m_mainMemory->Write(address, value);

    m_programCounter++;
    m_cycles += 8;
}

void Cpu::LoadImmediate16BitValue(uint8_t& high, uint8_t& low) {
    high = m_mainMemory->Read(m_programCounter + 2);
    low = m_mainMemory->Read(m_programCounter + 1);

    m_programCounter += 3;
    m_cycles += 12;
}

void Cpu::LoadImmediate16BitValue(uint16_t& to) {
    auto value = CombineRegisters(m_mainMemory->Read(m_programCounter + 2), m_mainMemory->Read(m_programCounter + 1));
    to = value;

    m_programCounter += 3;
    m_cycles += 12;
}

void Cpu::LoadStackPointerFromHL() {
    auto value = CombineRegisters(m_regH, m_regL);
    m_stackPtr = value;

    m_programCounter++;
    m_cycles += 8;
}
    

void Cpu::IncrementAtAddress(uint16_t address) {
    
    uint8_t value = m_mainMemory->Read(address);

    if ( (((value & 0xf) + ( (value +1) &0xf)) & 0x10) == 0x10) {
        m_regF.set(5);
    } 

    value++;

    if(value == 0) {
        m_regF.set(7);
    }

    m_regF.reset(6);

    m_mainMemory->Write(address, value);

    m_programCounter++;
    m_cycles += 12;
}

void Cpu::IncrementRegisterPair(uint8_t& high, uint8_t& low) {
    
    uint16_t value = CombineRegisters(high, low);
    value++;

    high = value >> 8;
    low = value;

    m_programCounter++;
    m_cycles += 8;
}

void Cpu::IncrementStackpointer() {
    m_stackPtr++;

    m_programCounter++;
    m_cycles += 8;
}

void Cpu::DecrementRegisterPair(uint8_t& high, uint8_t& low) {
        uint16_t value = CombineRegisters(high, low);
        value--;

        high = value >> 8;
        low = value;

        m_programCounter++;
        m_cycles+= 8;
}

void Cpu::DecrementStackPointer() {
    m_stackPtr--;

    m_programCounter++;
    m_cycles += 8;
}

void Cpu::DecrementAtAddress(uint16_t address) {
    
    auto value = m_mainMemory->Read(address);
    value--;

    m_mainMemory->Write(address, value);

    m_programCounter++;
    m_cycles += 12;
}


void Cpu::RLCA() {

    if ( (m_regA & 0b10000000) == 0b10000000) {
        m_regF.set(4);
    } else {
        m_regF.reset(4);
    }

    m_regA = m_regA << 1;

    if (m_regA == 0) {
        m_regF.set(7);
    }

    m_regF.reset(6);
    m_regF.reset(5);

    m_programCounter++;
    m_cycles += 4;
}

void Cpu::JumpRelative() {

    auto r8 = m_mainMemory->Read(m_programCounter + 1);
    m_programCounter += static_cast<int16_t>(r8);
    m_cycles += 8;
}

void Cpu::JumpRelativeZ() {

    if(m_regF.test(7)) {
        m_programCounter += static_cast<int16_t>(m_mainMemory->Read(m_programCounter + 1));
    } else {
        m_programCounter++;
    }

    m_cycles += 8;
}

void Cpu::RetNZ() {
    if(!m_regF.test(7)) {
        Ret();
    } else {
        m_programCounter++;
        m_cycles += 8;
    }
}

void Cpu::Jump() {
    auto address = CombineRegisters(m_mainMemory->Read(m_programCounter + 2), m_mainMemory->Read(m_programCounter + 1));
    
    m_programCounter = address;
    m_cycles += 12;
}
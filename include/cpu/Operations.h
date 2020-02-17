#include <stdexcept>
#include <string>
#include <cpu/Cpu.h>

class UnimplementedOperation : public std::runtime_error {
public:

    UnimplementedOperation(const std::string& msg);
};

void NOP();
void STOP();
void HALT();
void RST();
void DI();

void LDB(Cpu& cpu);
void LDC(Cpu& cpu);
void LDD(Cpu& cpu);
void LDE(Cpu& cpu);
void LDH(Cpu& cpu);
void LDL(Cpu& cpu);
void LDBC(Cpu& cpu);
void LD_ADDR_BC_A(Cpu& cpu);

void INCA(Cpu& cpu);
void INCB(Cpu& cpu);
void INCC(Cpu& cpu);
void INCD(Cpu& cpu);
void INCE(Cpu& cpu);
void INCH(Cpu& cpu);
void INCL(Cpu& cpu);

void INCBC(Cpu& cpu);
void INCDE(Cpu& cpu);
void INCHL(Cpu& cpu);

void DECA(Cpu& cpu);
void DECB(Cpu& cpu);
void DECC(Cpu& cpu);
void DECE(Cpu& cpu);
void DECD(Cpu& cpu);
void DECH(Cpu& cpu);
void DECL(Cpu& cpu);
void DECSP(Cpu& cpu);

void DECBC(Cpu& cpu);
void DECDE(Cpu& cpu);
void DECHL(Cpu& cpu);


void SCF(Cpu& cpu);
void CCF(Cpu& cpu);

void RLCA(Cpu& cpu);
#include <FlagRegister.h>


uint8_t FlagRegister::asByte() const {
    return 0;
}

void FlagRegister::flipCarry() 
{        
    if (m_carryFlag == FlagState::Set) {
        m_carryFlag = FlagState::Reset;
    } else {
        m_carryFlag = FlagState::Set;
    }
}
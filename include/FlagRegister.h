#pragma once

#include <cstdint>

enum class FlagState {
    Set,
    Reset
};

class FlagRegister {
public:

    constexpr void setCarry() {m_carryFlag = FlagState::Set;}
    constexpr void setHalfCarry() {m_halfCarryFlag = FlagState::Set;}
    constexpr void setZero() {m_zeroFlag = FlagState::Set;}
    constexpr void setSubtract() {m_subtractFlag = FlagState::Set;}

    constexpr void resetCarry() {m_carryFlag = FlagState::Reset;}
    constexpr void resetHalfCarry() {m_halfCarryFlag = FlagState::Reset;}
    constexpr void resetZero() {m_zeroFlag = FlagState::Reset;}
    constexpr void resetSubtract() {m_subtractFlag = FlagState::Reset;}

    constexpr FlagState carryFlag() const {return m_carryFlag;}
    constexpr FlagState halfCarryFlag() const {return m_halfCarryFlag;}
    constexpr FlagState zeroFlag() const {return m_zeroFlag;}
    constexpr FlagState subtractFlag() const {return m_subtractFlag;}

    void flipCarry();
    uint8_t asByte() const;

private:

    FlagState m_zeroFlag = FlagState::Set;
    FlagState m_subtractFlag = FlagState::Reset;
    FlagState m_halfCarryFlag = FlagState::Set;
    FlagState m_carryFlag = FlagState::Set;
};

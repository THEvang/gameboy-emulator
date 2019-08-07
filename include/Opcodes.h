#pragma once

#include <GameBoy.h>

void LoadRegister(GameBoy::Byte& destination, const GameBoy::Byte source);

GameBoy::Byte AddRegisters(const GameBoy::Byte lhs, const GameBoy::Byte& rhs, std::bitset<8>& flags);
GameBoy::Byte SubtractRegisters(const GameBoy::Byte& lhs, const GameBoy::Byte& rhs, std::bitset<8>& flags);

void Increment8Bit();
void Increment16Bit();

uint16_t CombineRegisters(const GameBoy::Byte high, const GameBoy::Byte low);


inline void NoOperation()
{
    return;
}


void UnimplementedOperation(const std::string& operation);

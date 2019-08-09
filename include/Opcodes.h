#pragma once

#include <GameBoy.h>
#include <string>

void NoOperation();

void LoadRegister(GameBoy::Byte& destination, const GameBoy::Byte source);

GameBoy::Byte AddRegisters(const GameBoy::Byte lhs, const GameBoy::Byte& rhs, std::bitset<8>& flags);
GameBoy::Byte SubtractRegisters(const GameBoy::Byte& lhs, const GameBoy::Byte& rhs, std::bitset<8>& flags);

uint16_t CombineRegisters(const GameBoy::Byte high, const GameBoy::Byte low);

void UnimplementedOperation(const std::string& operation);

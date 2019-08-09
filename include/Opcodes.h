#pragma once

#include <GameBoy.h>
#include <string>

void NoOperation();

void LoadRegister(GameBoy::Byte& destination, const GameBoy::Byte source);

void AddRegisters(GameBoy::Byte& to, const GameBoy::Byte& from, std::bitset<8>& flags);
void SubtractRegisters(GameBoy::Byte& to, const GameBoy::Byte& from, std::bitset<8>& flags);

uint16_t CombineRegisters(const GameBoy::Byte high, const GameBoy::Byte low);

void UnimplementedOperation(const std::string& operation);

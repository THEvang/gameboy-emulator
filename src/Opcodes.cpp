#include <Opcodes.h>
#include <iostream>

void NoOperation() {
    return;
}

void UnimplementedOperation(const std::string& operation) {
    std::cerr << "Unimplemented operation: \t" << operation << "\n";
}

GameBoy::Byte AddRegisters(const GameBoy::Byte& rhs, const GameBoy::Byte& lhs, std::bitset<8>& flags) {

    auto result = rhs + lhs;

    //Set flags

    return result;
}

uint16_t CombineRegisters(const GameBoy::Byte high, const GameBoy::Byte low) {
    return 0;
}
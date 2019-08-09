#include <Opcodes.h>
#include <iostream>

void NoOperation() {
    return;
}

void UnimplementedOperation(const std::string& operation) {
    std::cerr << "Unimplemented operation: \t" << operation << "\n";
}

void AddRegisters(GameBoy::Byte& to, const GameBoy::Byte& from, std::bitset<8>& flags) {

    to += from;

    //Set flags
}

uint16_t CombineRegisters(const GameBoy::Byte high, const GameBoy::Byte low) {

    uint16_t combinedRegister = (high << 8) | low;

    return combinedRegister;
}

void LoadRegister(GameBoy::Byte& destination, const GameBoy::Byte source) {
    destination = source;
}
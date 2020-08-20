#pragma once

#include <functional>
#include <exception>
#include <string>

#include "Cpu/Cpu.hpp"

#include "Cpu/Opcodes.hpp"
#include "Cpu/CBOpcodes.hpp"

class UnimplementedOperation : public std::runtime_error {
public:
    explicit UnimplementedOperation(const std::string& msg)
        : runtime_error(msg) {
    }
};

using Operation = std::function<int(Cpu&)>;

struct FetchResult {
    int delta_pc = 0;
    Operation operation;
};

FetchResult fetch(Opcode opcode);
FetchResult fetch_cb(CBCode opcode);
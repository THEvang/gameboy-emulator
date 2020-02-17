#pragma once

#include "MemoryBankController.h"

class MBC1 : public MemoryBankController {
public:

    uint8_t read(const uint16_t address) override;
    void write(const uint16_t address, const uint8_t value) override;

private:
};
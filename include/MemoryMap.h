#pragma once 

#include <memory>
#include <vector>

#include <Cartridge.h>

enum class BankingMode {
    RomBanking,
    RamBanking,
};

enum class ExternalRam {
    Enabled,
    Disabled
};

class MemoryMap {
public:

    MemoryMap(const std::shared_ptr<Cartridge> cartridge);

    void Write(const uint16_t address, const uint8_t value);

    uint8_t Read(const uint16_t address) const;

private:

    void LoadRomBank(int nr);

    std::vector<uint8_t> m_memory;
    std::shared_ptr<Cartridge> m_cartridge;

    ExternalRam m_externalRam = ExternalRam::Disabled;
    BankingMode m_bankingMode = BankingMode::RomBanking;
};
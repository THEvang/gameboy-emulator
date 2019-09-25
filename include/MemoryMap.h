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

    MemoryMap(std::shared_ptr<Cartridge> const & cartridge);

    void Write(uint16_t const address, uint8_t const value);

    uint8_t Read(uint16_t const address) const;

private:

    void LoadRomBank(int const nr);
    void LoadRamBank(int const nr);

    std::vector<uint8_t> m_memory;
    std::shared_ptr<Cartridge> m_cartridge;

    uint8_t m_currentRomBank;
    uint8_t m_currentRamBank;

    ExternalRam m_externalRam = ExternalRam::Disabled;
    BankingMode m_bankingMode = BankingMode::RomBanking;
};
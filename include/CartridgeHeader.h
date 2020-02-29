#include <string>

enum class ROMSize {
    
};

enum class DestinationCode {
    Japanese,
    NonJapanese
};


struct CartridgeHeader {
    std::string title;
    std::string manufacturerCode;
    ROMSize romSize;
    DestinationCode destinationCode;  
};
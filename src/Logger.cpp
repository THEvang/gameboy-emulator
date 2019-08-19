#include <Logger.h>

Logging Logger::logging = Logging::Off;

void Logger::Log(const LogLevel& logLevel, const std::string& msg) {
    if(logging == Logging::On) {
            
        switch(logLevel) {
            case LogLevel::Debug:
                std::cout << msg;
                break;
            case LogLevel::Warning:
                std::cout << msg;                
                break;
            case LogLevel::Error:
                std::cerr << msg;
                break;

        }
        std::cout << "\n";

    }
}
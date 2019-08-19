#pragma once

#include <string>
#include <iostream>

enum class LogLevel {
    Debug,
    Warning,
    Error
};

enum class Logging {
    On,
    Off
};


class Logger {
public:

    static void Log(const LogLevel& logLevel, const std::string& msg);

    static Logging logging;
};

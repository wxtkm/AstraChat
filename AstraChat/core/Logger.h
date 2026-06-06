#pragma once

#include <string>

class Logger {
public:
    static void info(const std::string& msg);

    static void warning(const std::string& msg);

    static void error(const std::string& msg);
};
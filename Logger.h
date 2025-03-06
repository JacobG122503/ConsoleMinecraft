#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <ctime>
#include <iomanip>
#include <cstdarg>

//Turn logging off, set it to false.
#define ENABLE_LOGGING true

inline void Log(const char* format, ...) {
    if (!ENABLE_LOGGING) return;
    std::ofstream file("logs.txt", std::ios::app);
    if (!file.is_open()) return;

    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    file << std::put_time(localTime, "[%Y-%m-%d %H:%M:%S] - ");

    va_list args;
    va_start(args, format);
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    file << buffer << std::endl;
}

#endif

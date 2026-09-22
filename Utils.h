#ifndef UTILS_H
#define UTILS_H

#include <string>
//#include <thread>
//#include <chrono>


class Utils {
public:
    static void printFormatted(const std::string& message, char borderChar = '-');
    static void delay(int milliseconds);
};

#endif

#include "Utils.h"
#include <iostream>
#include <ctime>  // 引入 <ctime> 來使用 clock()

void Utils::printFormatted(const std::string& message, char borderChar) {
    int length = message.length() + 4; // 邊界包含前後的空格
    for (int i = 0; i < length; ++i) {
        std::cout << borderChar;
    }
    std::cout << std::endl;
    std::cout << borderChar << " " << message << " " << borderChar << std::endl;
    for (int i = 0; i < length; ++i) {
        std::cout << borderChar;
    }
    std::cout << std::endl;
}

void Utils::delay(int milliseconds) {
    // 獲取當前的時間點
    clock_t start_time = clock();
    // 等待直到超過指定的毫秒數
    while (clock() - start_time < milliseconds * CLOCKS_PER_SEC / 1000) {
        // 做空迴圈來延遲
    }
}

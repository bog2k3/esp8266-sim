#include <Arduino.h>

#include <thread>

void delay(unsigned long milisec) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milisec));
}
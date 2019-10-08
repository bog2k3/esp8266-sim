#include <Arduino.h>

#include <thread>

void delay(unsigned long milisec) {
    if (false) { // if you really want to wait, change to true, but seriously?
        std::this_thread::sleep_for(std::chrono::milliseconds(milisec));
    }
}

unsigned long millis(void) {
    // witness how complicated STD had to make this shit:
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now().time_since_epoch()
    ).count();
}

void yield(void) {
    std::this_thread::yield();
}
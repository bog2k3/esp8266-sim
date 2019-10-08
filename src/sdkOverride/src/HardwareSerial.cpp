#include "HardwareSerial.h"

HardwareSerial Serial(0);
HardwareSerial Serial1(1);

HardwareSerial::HardwareSerial(int uart_nr) {

}

void HardwareSerial::begin(unsigned long baud, SerialConfig config, SerialMode mode, uint8_t tx_pin) {
    //throw "not implemented";
}

void HardwareSerial::end() {
    //throw "not implemented";
}

size_t HardwareSerial::setRxBufferSize(size_t size) {
    //throw "not implemented";
    return size;
}

int HardwareSerial::available(void) {
    throw "not implemented";
}

size_t HardwareSerial::readBytes(char* buffer, size_t size) {
    throw "not implemented";
}

void HardwareSerial::flush(void) {
    fflush(nullptr);
}

void HardwareSerial::setDebugOutput(bool) {
    throw "not implemented";
}

void HardwareSerial::startDetectBaudrate() {
    throw "not implemented";
}

unsigned long HardwareSerial::testBaudrate() {
    throw "not implemented";
}

unsigned long HardwareSerial::detectBaudrate(time_t timeoutMillis) {
    throw "not implemented";
}
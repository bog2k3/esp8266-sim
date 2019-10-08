#include <cstdlib>
#include <string>
#include <cstring>

#ifdef __cplusplus
extern "C"{
#endif

int atoi(const char *s) {
    return std::atoi(s);
}

long atol(const char* s) {
    return std::atol(s);
}

double atof(const char* s) {
    return std::atof(s);
}

char* itoa (int val, char *s, int radix) {
    return strdup(std::to_string(val).c_str());
}

char* ltoa (long val, char *s, int radix) {
    return strdup(std::to_string(val).c_str());
}

char* utoa (unsigned int val, char *s, int radix) {
    return strdup(std::to_string(val).c_str());
}

char* ultoa (unsigned long val, char *s, int radix) {
    return strdup(std::to_string(val).c_str());
}
 
char* dtostrf (double val, signed char width, unsigned char prec, char *s) {
    return strdup(std::to_string(val).c_str());
}

void reverse(char* begin, char* end) {
    throw "not implemented";
}

#ifdef __cplusplus
}
#endif

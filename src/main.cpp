#include <cstdio>

extern void setup();
extern void loop();

int main(int argc, char** argv) {
    printf("Simulator started.\n");
    printf("   >>> Calling setup()...");
    setup();
    printf("   >>> setup() finished.");
    printf("   >>> Calling loop()...");
    loop();
    printf("   >>> loop() finished.");
    return 0;
}
#include <cstdio>

#ifdef __cplusplus
extern "C" {
#endif
void setup();
void loop();
#ifdef __cplusplus
}
#endif

int main(int argc, char** argv) {
    try {
        printf("\nSimulator started.\n");
        printf("\n   >>> Calling setup()...\n");
        setup();
        printf("\n   >>> setup() finished.\n");
        printf("\n   >>> Calling loop()...\n");
        loop();
        printf("\n   >>> loop() finished.\n"); 
        return 0;
    } catch (const char* err) {
        fflush(nullptr);
        fprintf(stderr, "\n\nUncaught exception:\n%s\n\nQuiting.\n\n", err);
        fflush(nullptr);
    }
}
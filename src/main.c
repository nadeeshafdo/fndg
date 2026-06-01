#include "traverse.h"
#include "defs.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
void setup_windows_console() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

int main(int argc, char **argv) {
#ifdef _WIN32
    setup_windows_console();
#endif

    if (argc == 2 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)) {
        printf("fndg %s (c) 2026 nadeeshafdo\n", VERSION);
        return 0;
    }
    
    if (argc < 2) {
        printf("fndg %s (c) 2026 nadeeshafdo\n", VERSION);
        fprintf(stderr, "Usage: %s <search_term> [directory]\n", argv[0]);
        fprintf(stderr, "       %s --version\n", argv[0]);
        return 1;
    }
    
    const char *term = argv[1];
    const char *dir = (argc >= 3) ? argv[2] : ".";
    
    traverse(dir, term);
    return 0;
}

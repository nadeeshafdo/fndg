#include "search.h"
#include "defs.h"
#include <stdio.h>
#include <string.h>

bool is_binary(const char *filepath) {
    FILE *f = fopen(filepath, "rb");
    if (!f) return true; 
    
    char buf[1024];
    size_t bytes = fread(buf, 1, sizeof(buf), f);
    fclose(f);
    
    for (size_t i = 0; i < bytes; i++) {
        if (buf[i] == '\0') return true;
    }
    return false;
}

void search_file(const char *filepath, const char *filename, const char *term) {
    if (strstr(filename, term) != NULL) {
        printf("\033[1;32m[NAME MATCH]\033[0m %s\n", filepath);
    }

    if (is_binary(filepath)) return;

    FILE *f = fopen(filepath, "r");
    if (!f) return;

    char line[BUFFER_SIZE];
    size_t line_num = 1;
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, term) != NULL) {
            line[strcspn(line, "\n")] = 0; 
            printf("\033[1;34m[CONTENT]\033[0m %s:%zu: %s\n", filepath, line_num, line);
        }
        line_num++;
    }
    fclose(f);
}

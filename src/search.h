#ifndef SEARCH_H
#define SEARCH_H
#include <stdbool.h>

bool is_binary(const char *filepath);
void search_file(const char *filepath, const char *filename, const char *term);

#endif

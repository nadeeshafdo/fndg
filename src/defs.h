#ifndef DEFS_H
#define DEFS_H

#ifndef VERSION
#define VERSION "unknown"
#endif

#define MAX_PATH 4096
#define BUFFER_SIZE 8192

#ifdef _WIN32
#define lstat stat
#endif

#endif

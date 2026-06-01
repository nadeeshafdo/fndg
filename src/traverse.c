#include "traverse.h"
#include "search.h"
#include "defs.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void traverse(const char *dir_path, const char *term) {
    DIR *dir = opendir(dir_path);
    if (!dir) return;

    struct dirent *entry;
    char path[MAX_PATH];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

        struct stat statbuf;
        if (lstat(path, &statbuf) == -1) continue;

        if (S_ISDIR(statbuf.st_mode)) {
            traverse(path, term);
        } else if (S_ISREG(statbuf.st_mode)) {
            search_file(path, entry->d_name, term);
        }
    }
    closedir(dir);
}

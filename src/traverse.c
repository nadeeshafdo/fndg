#include "traverse.h"
#include "search.h"
#include "defs.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#ifndef _WIN32
#include <unistd.h>
#endif

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif

#ifdef _WIN32
void traverse(const char *dir_path, const char *term) {
    WIN32_FIND_DATAA find_data;
    HANDLE find_handle;
    char search_path[MAX_PATH];
    char path[MAX_PATH];
    
    snprintf(search_path, sizeof(search_path), "%s\\*", dir_path);
    
    find_handle = FindFirstFileA(search_path, &find_data);
    if (find_handle == INVALID_HANDLE_VALUE) return;
    
    do {
        if (strcmp(find_data.cFileName, ".") == 0 || strcmp(find_data.cFileName, "..") == 0)
            continue;
            
        snprintf(path, sizeof(path), "%s\\%s", dir_path, find_data.cFileName);
        
        if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            traverse(path, term);
        } else {
            search_file(path, find_data.cFileName, term);
        }
    } while (FindNextFileA(find_handle, &find_data));
    
    FindClose(find_handle);
}
#else
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
#endif

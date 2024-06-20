#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_PATH_LENGTH 1000

void count_lines_in_file(const char *filepath, int *line_count) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            (*line_count)++;
        }
    }

    fclose(file);
}

void traverse_directory(const char *dirpath, int *total_lines) {
    DIR *dir = opendir(dirpath);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        char path[MAX_PATH_LENGTH];

        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", dirpath, entry->d_name);

        if (entry->d_type == DT_DIR) {
            // Recur for subdirectories
            traverse_directory(path, total_lines);
        } else if (entry->d_type == DT_REG) {
            // Check for .txt files
            const char *ext = strrchr(entry->d_name, '.');
            if (ext && strcmp(ext, ".txt") == 0) {
                count_lines_in_file(path, total_lines);
            }
        }
    }

    closedir(dir);
}

int main() {
    char dirpath[MAX_PATH_LENGTH];

    printf("Enter the directory path: ");
    scanf("%s", dirpath);

    int total_lines = 0;
    traverse_directory(dirpath, &total_lines);

    printf("Total number of lines in .txt files: %d\n", total_lines);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_utils.h"

int load_dataset(const char* path, const int n, int *const m) {
    int i, j;
    FILE *file;

    file = fopen(path, "r");
    if (file == NULL) {
        perror("Error opening file: ");
        return EXIT_FAILURE;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (!fscanf(file, "%d", &m[i * n + j])) {
                break;
            }
            if (m[i * n + j] == -1) {
                m[i * n + j] = INF;
            }
        }
    }
    if (fclose(file) != 0) {
        perror("Error closing file: ");
    }
    return EXIT_SUCCESS;
}


int compare(const int *const m1, const int *const m2, const int n) {
   int equal;

   equal = memcmp(m1, m2, n * n * sizeof(int));
   return equal == 0 ? 1 : 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "floyd_warshall.h"

int floyd_warshall(int* graph, int n, int* apsp, t_error* err) {
	int i, j, k;

    memcpy(apsp, graph, n * n * sizeof(int));
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (apsp[i * n + j] > apsp[i * n + k] + apsp[k * n + j]) {
                    apsp[i * n + j] = apsp[i * n + k] + apsp[k * n + j];
                }
            }
        }
    }
    return EXIT_SUCCESS;
}
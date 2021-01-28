#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include "benchmark_utils.h"

int inf = INT_MAX / 2;
double prob_inf = 0.1;
int seed = 12345;
int max_value = 20;

void print_results(const bench_res *const results, const int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d\t%f\n", results[i].n, results[i].exe_time);
    }
}

int gen_graph(const int n, int *const graph, t_error *err) {

    // check that n > 0
    if (n <= 0) {
		err->err_code = WRONG_NUM_OF_NODES_ERR;
		snprintf(err->err_msg, sizeof(err->err_msg), "%s", "n should be > 0");
        return EXIT_FAILURE;
    }

    int rand_max = max_value;
    int i, j, rand_value;
    srand(seed);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j) {
                graph[i * n + j] = 0;
            } else {
                rand_value = rand() % rand_max;
                graph[i * n + j] = (((double)rand_value / (double)rand_max) <= prob_inf) ? inf : rand_value;
            }
        }
    }
    return EXIT_SUCCESS;
}


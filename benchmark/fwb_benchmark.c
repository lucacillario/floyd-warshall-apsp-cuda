#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "../lib/blocked_floyd_warshall.h"
#include "benchmark_utils.h"


/**
 * @param from_n initial number of nodes
 * @param to_n final number of nodes
 * @param step between one configuration and the next one
 * @param b block size
 */
int run_benchmark(const int from_n, const int to_n, const int step, const int b) {
    int i;

    // calculating the number of benchmark configurations
    int num_of_configs = 0;
    for (i = from_n; i <= to_n; i+=step) {
        num_of_configs++;
    }

    // allocating results matrix
    bench_res *results = malloc(num_of_configs * sizeof(bench_res));
    assert(results != NULL);

    // filling results array with the benchmark configurations
    int temp;
    for (i = 0, temp = from_n; i < num_of_configs; i++, temp += step) {
        results[i].n = temp;
    }

    // benchmark
    int status;
	t_error err;
	for (i = 0; i < num_of_configs; i++) {
        int n = results[i].n;
        int *m = malloc(n * n * sizeof(int));
        assert(m != NULL);
        status = gen_graph(n, m, &err);
		if (status != 0) {
			fprintf(stderr, "Error during random graph generation: %s", err.err_msg);
			return EXIT_FAILURE;
		}
        int *apsp = malloc(n * n * sizeof(int));
        assert(apsp != NULL);
        clock_t start = clock();
        status = blocked_floyd_warshall(m, n, b, apsp, &err);
        if (status != 0) {
			fprintf(stderr, "Error during blocked floyd warshall execution: %s", err.err_msg);
			return EXIT_FAILURE;
        }
        clock_t end = clock();
        results[i].exe_time = (double)(end - start) / CLOCKS_PER_SEC;
        free(m);
        free(apsp);
    }

    print_results(results, num_of_configs);
	free(results);
	return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
	if (argc != 5) {
		return EXIT_FAILURE;
	}
	const int from_n = atoi(argv[1]);
	const int to_n = atoi(argv[2]);
	const int step = atoi(argv[3]);
	const int b = atoi(argv[4]);

    return run_benchmark(from_n, to_n, step, b);
}

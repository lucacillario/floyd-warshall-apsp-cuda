#include <stdlib.h>
#include <stdio.h>
#include "test_utils.h"
#include "minunit.h"
#include "../benchmark/benchmark_utils.h"

int tests_run = 0;

static char* gen_graph_test() {
	int exit_code, n;
	t_error err;

	n = 0;
	exit_code = gen_graph(n, NULL, &err);
	mu_assert("Zero nodes - check for failure", exit_code == EXIT_FAILURE);
	mu_assert("Zero nodes - check error code", err.err_code == WRONG_NUM_OF_NODES_ERR);

	n = 10;
	int *g1 = malloc(n * n * sizeof(int));
	exit_code = gen_graph(n, g1, &err);
	mu_assert("Random gen of 10x10 graph", exit_code == EXIT_SUCCESS);

	int *g2 = malloc(n * n * sizeof(int));
	exit_code = gen_graph(n, g2, &err);
	mu_assert("Random gen of 10x10 graph", exit_code == EXIT_SUCCESS);

	mu_assert("Same seed, should lead to same graphs", compare(g1, g2, n));

	free(g1);
	free(g2);

	return 0;
}

static char* all_tests() {
	mu_run_test(gen_graph_test);
	return 0;
}

int main(int argc, char **argv) {
	char *result = all_tests();
	if (result != 0) {
		printf("%s\n", result);
	} else {
		printf("ALL TESTS PASSED\n");
	}
	printf("Tests run: %d\n", tests_run);

	return result != 0;
}



#include <stdlib.h>
#include <stdio.h>
#include "test_utils.h"
#include "minunit.h"
#include "../lib/blocked_floyd_warshall.h"

int tests_run = 0;

static char* wrong_nodes_num() {
	int exit_code;
	t_error err;

	exit_code = blocked_floyd_warshall(NULL, 0, 0, NULL, &err);
	mu_assert("Zero nodes - check for failure", exit_code == EXIT_FAILURE);
	mu_assert("Zero nodes - check error code", err.err_code == WRONG_NUM_OF_NODES_ERR);

	return 0;
}

static char* wrong_block_size() {
	int n, exit_code;
	t_error err;

	n = 10;

	exit_code = blocked_floyd_warshall(NULL, n, 0, NULL, &err);
	mu_assert("Zero blocks - check for failure", exit_code == EXIT_FAILURE);
	mu_assert("Zero blocks - check error code", err.err_code == WRONG_BLOCK_SIZE_ERR);

	exit_code = blocked_floyd_warshall(NULL, n, n + 1, NULL, &err);
	mu_assert("Blocks > n - check for failure", exit_code == EXIT_FAILURE);
	mu_assert("Blocks > n - check error code", err.err_code == WRONG_BLOCK_SIZE_ERR);
	return 0;
}

static char* small_dataset_test() {
    int *dataset, *obtained_m, *expected_m, n, b, exit_code;
    const char *dataset_path, *solution_path;

    n = 10;
    b = 2;

    dataset = malloc(n * n * sizeof(int));
	mu_assert("Check not null", dataset != NULL);
    dataset_path = "test/dataset/dataset_10_10.csv";
    mu_assert("Loading 10x10 dataset", load_dataset(dataset_path, n, dataset) == 0);

    obtained_m = malloc(n * n * sizeof(int));
	mu_assert("Check not null", obtained_m != NULL);
    exit_code = blocked_floyd_warshall(dataset, n, b, obtained_m, NULL);
	mu_assert("Check that BFW succeeded", exit_code == EXIT_SUCCESS);

	expected_m = malloc(n * n * sizeof(int));
	mu_assert("Check not null", expected_m != NULL);
    solution_path = "test/dataset/solution_10_10.csv";
    mu_assert("Loading 10x10 dataset solution", load_dataset(solution_path, n, expected_m) == 0);

    mu_assert("Comparing results", compare(obtained_m, expected_m, n));

    b = 4;
    exit_code = blocked_floyd_warshall(dataset, n, b, obtained_m, NULL);
	mu_assert("Check that BFW succeeded, with n % b != 0", exit_code == EXIT_SUCCESS);
	mu_assert("Comparing results", compare(obtained_m, expected_m, n));

	free(dataset);
	free(obtained_m);
	free(expected_m);

    return 0;
}

static char* medium_dataset_test() {
    int *dataset, *obtained_m, *expected_m, n, b, exit_code;
    const char *dataset_path, *solution_path;

    n = 50;
    b = 5;

    dataset = malloc(n * n * sizeof(int));
	mu_assert("Check not null", dataset != NULL);
    dataset_path = "test/dataset/dataset_50_50.csv";
    mu_assert("Loading 50x50 dataset", load_dataset(dataset_path, n, dataset) == 0);

    obtained_m = malloc(n * n * sizeof(int));
	mu_assert("Check not null", obtained_m != NULL);
	exit_code = blocked_floyd_warshall(dataset, n, b, obtained_m, NULL);
	mu_assert("Check that BFW succeeded", exit_code == EXIT_SUCCESS);

	expected_m = malloc(n * n * sizeof(int));
	mu_assert("Check not null", expected_m != NULL);
    solution_path = "test/dataset/solution_50_50.csv";
    mu_assert("Loading 50x50 dataset solution", load_dataset(solution_path, n, expected_m) == 0);

    mu_assert("Comparing results", compare(obtained_m, expected_m, n));

    b = 17;
	exit_code = blocked_floyd_warshall(dataset, n, b, obtained_m, NULL);
	mu_assert("Check that BFW succeeded, with n % b != 0", exit_code == EXIT_SUCCESS);
	mu_assert("Comparing results", compare(obtained_m, expected_m, n));

	free(dataset);
	free(obtained_m);
	free(expected_m);

    return 0;
}

static char* big_dataset_test() {
    int *dataset, *obtained_m, *expected_m, n, b, exit_code;
    const char *dataset_path, *solution_path;

    n = 100;
    b = 10;

    dataset = malloc(n * n * sizeof(int));
	mu_assert("Check not null", dataset != NULL);
    dataset_path = "test/dataset/dataset_100_100.csv";
    mu_assert("Loading 100x100 dataset", load_dataset(dataset_path, n, dataset) == 0);

    obtained_m = malloc(n * n * sizeof(int));
	mu_assert("Check not null", obtained_m != NULL);
	exit_code = blocked_floyd_warshall(dataset, n, b, obtained_m, NULL);
	mu_assert("Check that BFW succeeded", exit_code == EXIT_SUCCESS);

    expected_m = malloc(n * n * sizeof(int));
	mu_assert("Check not null", expected_m != NULL);
    solution_path = "test/dataset/solution_100_100.csv";
    mu_assert("Loading 100x100 dataset solution", load_dataset(solution_path, n, expected_m) == 0);

    mu_assert("Comparing results", compare(obtained_m, expected_m, n));

    b = 32;
	exit_code = blocked_floyd_warshall(dataset, n, b, obtained_m, NULL);
	mu_assert("Check that BFW succeeded, with n % b != 0", exit_code == EXIT_SUCCESS);
	mu_assert("Comparing results", compare(obtained_m, expected_m, n));

	free(dataset);
	free(obtained_m);
	free(expected_m);

    return 0;
}

static char* all_tests() {
	mu_run_test(wrong_nodes_num);
    mu_run_test(wrong_block_size);
    mu_run_test(small_dataset_test);
    mu_run_test(medium_dataset_test);
    mu_run_test(big_dataset_test);
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

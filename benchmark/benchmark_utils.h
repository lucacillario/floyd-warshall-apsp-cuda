#ifndef TYPEDEF_ERROR
#define TYPEDEF_ERROR
#include "../lib/errors.h"
#endif

/**
 * Infinity value
 */
extern int inf;


/**
 * Probability of infinity value in the random graph
 */
extern double prob_inf;


/**
 * Seed used in the generation of the random graph
 */
extern int seed;


/**
 * Max value allowed in the random graph
 */
extern int max_value;


/**
 * Benchmark execution time with a graph of n nodes.
 */
typedef struct benchmark_result {
    int n;
    double exe_time;
} bench_res;


/**
 * @param results of the benchmark
 * @param size of benchmark results
 */
void print_results(const bench_res *const results, const int size);


/**
 * Generates a random graph with values between 0 and max_value on non-diagonal positions
 * and zeros on diagonal positions.
 * @param n number of nodes
 * @param graph generated graph
 * @param err in case of error, this will contain some info about it
 * @return 0 on success, -1 on error
 */
int gen_graph(const int n, int *const graph, t_error *err);

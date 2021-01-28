#ifndef TYPEDEF_ERROR
#define TYPEDEF_ERROR
#include "../lib/errors.h"
#endif

/**
 * @param graph input graph
 * @param n number of graph's vertices
 * @param apsp all pairs shortest paths
 * @param err in case of error during the execution, this will contain some info about it
 * @return 0 if success, non-zero otherwise
 */
int floyd_warshall(int* graph, int n, int* apsp, t_error* err);

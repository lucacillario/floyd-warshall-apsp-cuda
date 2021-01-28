#include <limits.h>

/**
 * infinity, we can still safely add two infinities
 */
#define INF INT_MAX / 2

/**
 * Loads test dataset in memory.
 *
 * @param path of test dataset
 * @param n number of nodes
 * @param m matrix that will contain the dataset
 * @return 0 if success, 1 otherwise
 */
int load_dataset(const char* path, const int n, int *const m);

/**
 * Compares the obtained solution with the expected one.
 *
 * @param m1 obtained solution
 * @param m2 expected solution
 * @param n number of nodes
 * @return 1 if the two matrices are equal, 0 otherwise
 */
int compare(const int *const m1, const int *const m2, const int n);
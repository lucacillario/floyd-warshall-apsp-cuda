CC = gcc -O3
CU = nvcc
LIB = ar cr
FROM_N = 32
TO_N = 1024
STEP = 16
B = 8

fw_seq.o:
	@$(CC) -c -o .bin/fw_seq.o lib/floyd_warshall_sequential.c

bfw_naive_cuda.o:
	@$(CU) -c -o .bin/bfw_naive_cuda.o lib/blocked_floyd_warshall_cuda_naive.cu

bfw_cuda.o:
	@$(CU) -c -o .bin/bfw_cuda.o lib/blocked_floyd_warshall_cuda.cu

bench.a:
	@mkdir -p .bin
	@$(CC) -c -o .bin/fw_bench.o benchmark/fw_benchmark.c
	@$(CC) -c -o .bin/bench_utils.o benchmark/benchmark_utils.c
	@$(LIB) .bin/bench.a .bin/fw_bench.o .bin/bench_utils.o

bench_blocked.a:
	@mkdir -p .bin
	@$(CU) -c -o .bin/fwb_bench.o benchmark/fwb_benchmark.c
	@$(CU) -c -o .bin/bench_utils.o benchmark/benchmark_utils.c
	@$(LIB) .bin/bench_blocked.a .bin/fwb_bench.o .bin/bench_utils.o

bench_sequential: bench.a fw_seq.o
	@$(CC) -o .bin/bench_sequential .bin/bench.a .bin/fw_seq.o
	@./.bin/bench_sequential $(FROM_N) $(TO_N) $(STEP)

bench_naive_cuda: bench_blocked.a bfw_naive_cuda.o
	@$(CU) -o .bin/bench_naive_cuda .bin/bench_blocked.a .bin/bfw_naive_cuda.o
	@./.bin/bench_naive_cuda $(FROM_N) $(TO_N) $(STEP) $(B)

bench_cuda: bench_blocked.a bfw_cuda.o
	@$(CU) -o .bin/bench_cuda .bin/bench_blocked.a .bin/bfw_cuda.o
	@./.bin/bench_cuda $(FROM_N) $(TO_N) $(STEP) $(B)

bench: bench_sequential bench_naive_cuda bench_cuda

test.a:
	@mkdir -p .bin
	@$(CC) -c -o .bin/fw_test.o test/fw_test.c
	@$(CC) -c -o .bin/test_utils.o test/test_utils.c
	@$(LIB) .bin/test.a .bin/fw_test.o .bin/test_utils.o

test_blocked.a:
	@mkdir -p .bin
	@$(CU) -c -o .bin/bfw_test.o test/bfw_test.c
	@$(CU) -c -o .bin/test_utils.o test/test_utils.c 
	@$(LIB) .bin/test_blocked.a .bin/bfw_test.o .bin/test_utils.o

test_bench_utils:
	@$(CC) -c -o .bin/bench_utils.o benchmark/benchmark_utils.c
	@$(CC) -c -o .bin/test_utils.o test/test_utils.c
	@$(CC) -c -o .bin/test_bench_utils.o test/bench_utils_test.c
	@$(CC) -o .bin/test_bench_utils .bin/bench_utils.o .bin/test_utils.o .bin/test_bench_utils.o
	@./.bin/test_bench_utils

test_sequential: test.a fw_seq.o
	@$(CC) -o .bin/test_sequential .bin/test.a .bin/fw_seq.o
	@./.bin/test_sequential

test_naive_cuda: test_blocked.a bfw_naive_cuda.o
	@$(CU) -o .bin/test_naive_cuda .bin/test_blocked.a .bin/bfw_naive_cuda.o
	@./.bin/test_naive_cuda

test_cuda: test_blocked.a bfw_cuda.o
	@$(CU) -o .bin/test_cuda .bin/test_blocked.a .bin/bfw_cuda.o
	@./.bin/test_cuda

test: test_bench_utils test_sequential test_naive_cuda test_cuda

clean:
	@rm -rf .bin/

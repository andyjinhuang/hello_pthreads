#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

#define NUMTHREADS  4

// Work done by one thread
struct Work {
	int start; // first integer in range
	int len;   // how many integers in range
	int sum;   // result of thread's local computation
};

void *worker(void *arg)
{
	struct Work *work = arg;

	// local computation
	work->sum = 0;
	for (int i = work->start; i < work->start + work->len; i++) {
		work->sum += i;
	}

	return NULL;
}

int main(int argc, char **argv)
{
	int max;

	printf("Max int: " );
	scanf("%i", &max);

	// Divide up work
	struct Work workList[NUMTHREADS];
	pthread_t threadList[NUMTHREADS];

	int chunkSize = max / NUMTHREADS;
	for (int i = 0; i < NUMTHREADS; i++) {
		workList[i].start = 1 + (i * chunkSize);
		workList[i].len = chunkSize;
		if (i == NUMTHREADS - 1) {
			workList[i].len += (max % NUMTHREADS);
		}
	}

	// Start threads
	for (int i = 0; i < NUMTHREADS; i++) {
		pthread_create(&threadList[i], NULL, &worker, &workList[i]);
	}

	printf("Threads started\n");

	// Wait for threads to finish
	for (int i = 0; i < NUMTHREADS; i++) {
		pthread_join(threadList[i], NULL);
	}

	printf("Threads finished\n");

	// Combine results
	int global_sum = 0;
	for (int i = 0; i < NUMTHREADS; i++) {
		global_sum += workList[i].sum;
	}

	printf("Sum is %i\n", global_sum);

	return 0;
}

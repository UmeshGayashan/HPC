#include <stdlib.h>
#include <omp.h>
#include <stdio.h>
#define THREADS 8
#define N 100
int main ( ) {
 int i;
 #pragma omp parallel for num_threads(THREADS)
 for (i = 0; i < N; i++) {
 printf("Thread %d is doing iteration %d.\n", omp_get_thread_num(
), i);
 }
 /* all threads done */
 printf("All done!\n");
 return 0;
}
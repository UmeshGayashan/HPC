#include <omp.h>
#include <stdio.h>
#define CHUNKSIZE 100
#define N     1000

void main ()  
{

int i, chunk;
float a[N], b[N], c[N];

/* Some initializations */
for (i=0; i < N; i++)
  a[i] = b[i] = i * 1.0;
chunk = CHUNKSIZE;

#pragma omp parallel shared(a,b,c,chunk) private(i)
  {

  #pragma omp for schedule(dynamic,chunk) nowait
  for (i=0; i < N; i++)
    c[i] = a[i] + b[i];
    printf("Thread %d: c[%d]= %f\n", omp_get_thread_num(),i,c[i]);

  }  /* end of parallel section */
}

// https://hpc-tutorials.llnl.gov/openmp/do_for_directive/
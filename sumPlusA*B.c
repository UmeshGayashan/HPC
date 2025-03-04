#include <stdio.h>
#include <omp.h>

#define N 100  // Size of arrays

int main() {
    int A[N], B[N], sum = 0;
    
    // Initialize arrays
    for (int i = 0; i < N; i++) {
        A[i] = i;
        B[i] = i;
    }

    // Parallel computation of sum
    // #pragma omp parallel for → Tells OpenMP to parallelize the for loop.
    // reduction(+:sum) → Ensures that multiple threads safely update sum without race conditions.

    
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        #pragma omp critical // we are forcing to run this serial
        sum += A[i] * B[i]; // sum = sum + (A[i] * B[i])
    }

    printf("Sum = %i\n", sum);
    return 0;
}

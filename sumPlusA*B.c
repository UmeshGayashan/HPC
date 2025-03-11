#include <stdio.h>
#include <omp.h>

#define N 100  // Size of arrays

int main() {
    int A[N], B[N], sumOfForcing = 0,sumwithReduction = 0, sum = 0;
    
    // Initialize arrays
    for (int i = 0; i < N; i++) {
        A[i] = i;
        B[i] = i;
    }

    // without any parallelization
    for (int i = 0; i < N; i++) {
        sum += A[i] * B[i]; // sum = sum + (A[i] * B[i])
    }

    double start_time, end_time;
    // Measure time for reduction method
    start_time = omp_get_wtime();
    // Parallel computation of sum
    // #pragma omp parallel for → Tells OpenMP to parallelize the for loop.
    // reduction(+:sum) → Ensures that multiple threads safely update sum without race conditions.
    #pragma omp parallel for reduction(+:sumwithReduction)
    for (int i = 0; i < N; i++) {
        sumwithReduction += A[i] * B[i]; // sum = sum + (A[i] * B[i])
    }

    end_time = omp_get_wtime();
    printf("Time for reduction: %f seconds\n", end_time - start_time);


    // Measure time for forcing serial method
    start_time = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        #pragma omp critical // we are forcing to run this serial
        sumOfForcing += A[i] * B[i]; // sum = sum + (A[i] * B[i])
    }

    end_time = omp_get_wtime();
    printf("Time for forcing serial: %f seconds\n", end_time - start_time);

    // Measure time for using shared and private method
    start_time = omp_get_wtime();

    // using private and shared values

    int partial_Sum, total_Sum;

    #pragma omp parallel private(partial_Sum) shared(total_Sum)
    {
        partial_Sum = 0;
        total_Sum = 0;

        #pragma omp for
        for(int i = 0; i < N; i++){
            partial_Sum += A[i] * B[i];
        }

        //Create thread safe region.
        #pragma omp critical
        {
            //add each threads partial sum to the total sum
            total_Sum += partial_Sum;
        }
    }

    end_time = omp_get_wtime();
    printf("Time for shared and private: %f seconds\n", end_time - start_time);

    printf("Sum of Forcing to Serial = %i\nSum Using Reduction = %i\nUsing Shared and Private Sum: %d\n", sumOfForcing,sumwithReduction,total_Sum);
    return 0;
}

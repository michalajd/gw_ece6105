// mean_var.c
#include <upc_relaxed.h> // Header file

shared int A[N]; // the data
shared int B[THREADS]; // partial sums 

void main() {
    int i, mean, var;
    // partial sums
    upc_forall(i = 0; i < N; i++, i) { 
        B[i] = B[i] + A[i];
    }

    // find the mean
    for (i = 0; i < N; i++) {
        mean = mean + B[i];
    }

    mean = mean/N;

    // find the variance
    int temp; // for term inside square
    for (i = 0; i < N; i++) {
        temp = A[i] - mean;
        temp = pow(temp,2);
        var = var + temp;
    }

    var = var / N;

    // final prints
    printf("The mean is: %d", mean);
    printf("The variance is: %d", var);

}
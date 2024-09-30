// array_add.c
#include <upc_relaxed.h> // Header file for UPC

#define N = 100 * THREADS

shared int A[N], B[N], C[N]; // A and B are the ones being added, C is the sum

void main() {
    int i;
    upc_forall(i = 0; i < N; i++; i) { // Partitioned so each thread gets a sum
        C[i] = A[i] + B[i];
    }
}




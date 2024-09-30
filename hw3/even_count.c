// even_count.c
#include <upc_relaxed.h> // header file

shared int A[N]; // data
shared int local_count[THREADS]; // for partitioning

void main() {
    // find even numbers in A
    int i, temp, sum;
    upc_forall(i = 0; i < N; i++; i) {
        temp = A[i];
        if (temp % 2 == 0) local_count[i] = local_count[i] + 1;
    }

    // add values in "local_count"
    for (i = 0; i < THREADS; i++) {
        sum = sum + local_count[i];
    }

    printf("The number of even numbers in the array is %d", sum);
}


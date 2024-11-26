#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int A[256][256]; // data
int totals[256] = {0};

void main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // rank = processor's ID
    MPI_Comm_size(MPI_COMM_WORLD, &size); // size = number of processors

    /* Create random 256x256 array */
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            A[i][j] = rand() % (256);
        }
    }
    /* Defining critical variables */
    int elements_proc = 256 * 256 / size; // elements per processor
    int sub_A[elements_proc][elements_proc]; // buffer for subsets of A for each process

    /* Scatter elements */
    MPI_Scatter(A, elements_proc, MPI_INT, sub_A, elements_proc, MPI_INT, 0, MPI_COMM_WORLD);

    /* Find counts for all numbers 0-255 in each process */
    int process_total[256] = {0};
    for (int i = 0; i < elements_proc; i++) {
        for (int j = 0; j < elements_proc; j++) {
            for (int cnt = 0; cnt < 255; cnt++) {
            if (sub_A[i][j] == cnt) process_total[cnt]++;
            }
        }
    }

    /* Reduce back to process 0 */
    MPI_Reduce(process_total, totals, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    /* Generate histogram */
    if (rank == 0) {
        for (int i = 0; i < sizeof(totals); i++) {
            printf("[%d] ", i);
            for (int j = 0; j < totals[i]; j++) {
                printf("x");
            }
        printf("\n");
        }
    }

    /* End MPI program */
    MPI_Finalize();
}
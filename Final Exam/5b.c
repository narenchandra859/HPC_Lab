#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
	int rank, np, tmp;
	int data[] = {1,2,3,4,5,6};
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Scatter(data, 1, MPI_INT, &tmp, 1, MPI_INT, 0, MPI_COMM_WORLD);
	printf("\nIn rank %d received data %d", rank, tmp);
	MPI_Finalize();
	return 0;
}
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int data[] = {5,8,7,6};
	int rank;
	int i = -1;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Scatter((void*) data, 1, MPI_INT, (void*) &i, 1, MPI_INT, 0, MPI_COMM_WORLD);
	printf("\n[%d] received i = [%d]\n", rank, i);
	MPI_Finalize();
	return 0;
}
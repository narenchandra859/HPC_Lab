#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int numprocs, rank, i, src, dst, s = 0;
	int tmp;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank == 0) {
		for(i = 1; i < numprocs; i++) {
			src = i;
			MPI_Recv(&tmp, 1, MPI_INT, src, 0, MPI_COMM_WORLD, &status);
			s += tmp; 
		}
		printf("\nIn master thread [%d], sum to [%d] is = %d\n\n", rank, numprocs-1, s);
	}
	else {
		dst = 0;
		MPI_Send(&rank, 1, MPI_INT, dst, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
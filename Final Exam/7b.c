#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
	int rank, np, s, tmp, i;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	if(rank == 0) {
		s = 0;
		for(i = 1; i < np; i++) {
			MPI_Recv(&tmp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
			s += tmp;
		}
		printf("\nIn master processer [rank %d], Sum to N(%d) = %d\n", rank, np-1, s);
	}
	else {
		tmp = rank;
		MPI_Send(&tmp, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}
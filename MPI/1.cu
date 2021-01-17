#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
	int rank, size;
	double param[6], mine;
	int sndcnt, rcvcnt;
	int i;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	sndcnt = 1;
	mine = 5 + rank;
	if (rank == 0)
		rcvcnt = 1;
	MPI_Gather(&mine, sndcnt, MPI_DOUBLE, param, rcvcnt, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	if (rank == 0)
		for (i = 0; i < size; ++i)
			printf("In master(rank 0), paramater[%d] received is %f \n", i, param[i]);
	MPI_Finalize();
	return 0;
}
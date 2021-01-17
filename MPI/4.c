#include <stdio.h>
#include <math.h>
#include <mpi.h>
double func(double x)
{
  return (4.0 / (1.0 + x * x));
}
int main(int argc, char *argv[])
{
  int noInt, i;
  int rank, size;
  double mypi, h, sum, x;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if(!rank)
  {
    printf("\nEnter the number of intervals : ");
    scanf("%d", &noInt);
  }
  MPI_Bcast(&noInt, 1, MPI_INT, 0, MPI_COMM_WORLD);
  h = 1.0 / (double)noInt;
  sum = 0.0;
  for (i = rank + 1; i <= noInt; i += size)
  {
    x = h * ((double)i - 0.5);
    sum += func(x);
  }
  mypi = h * sum;
  MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  if (!rank)
    printf("\nPi is approximately %.16f\n\n", pi);
  MPI_Finalize();
  return 0;
}

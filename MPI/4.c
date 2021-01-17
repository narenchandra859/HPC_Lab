#include <stdio.h>
#include <math.h>
#include <mpi.h>
double func(double x)
{
  return (4.0 / (1.0 + x * x));
}
int main(int argc, char *argv[])
{
  int NoInterval, interval;
  int MyRank, Numprocs, Root = 0;
  double mypi, pi, h, sum, x;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &Numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);
  if (MyRank == Root)
  {
    printf("\nEnter the number of intervals : ");
    scanf("%d", &NoInterval);
  }
  MPI_Bcast(&NoInterval, 1, MPI_INT, 0, MPI_COMM_WORLD);
  h = 1.0 / (double)NoInterval;
  sum = 0.0;
  for (interval = MyRank + 1; interval <= NoInterval; interval += Numprocs)
  {
    x = h * ((double)interval - 0.5);
    sum += func(x);
  }
  mypi = h * sum;
  MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, Root, MPI_COMM_WORLD);
  if (MyRank == Root)
    printf("\nPi is approximately %.16f\n\n", pi);
  MPI_Finalize();
  return 0;
}
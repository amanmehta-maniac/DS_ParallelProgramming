#include <mpi.h>
#include <bits/stdc++.h>
 
int main (int argc, char* argv[])
{
  int rank, size;
  MPI::Status status;
  MPI_Init (&argc, &argv);      /* starts MPI */
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
  MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */


  if(rank==0){
  		
  }
  else{
  }
  // printf( "Hello world from process %d of %d\n", rank, size );
  MPI_Finalize();
  return 0;
}
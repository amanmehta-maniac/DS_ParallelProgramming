#include <mpi.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
    int my_rank, size;
       
    MPI::Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    cout << my_rank << endl;
    
    MPI_Finalize();
    return 0;
}

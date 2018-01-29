mpic++ -std=g++14 mpi_inverse.cpp -o code
mpirun -np 4 ./code

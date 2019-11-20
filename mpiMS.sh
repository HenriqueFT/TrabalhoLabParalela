mpicc MPI_Merge.c -o MPI_Merge.o 
time mpirun -np 4 ./MPI_Merge.o 
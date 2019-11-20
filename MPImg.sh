mpicc MPI_Merge_Gather.c -o MPI_Merge_Gather.o 
time mpirun -np 4 ./MPI_Merge_Gather.o 
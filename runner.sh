mpicc MPI_Merge_Gather.c -o MPI_Merge_Gather.o
gcc -fopenmp bitonic-sort-omp.c -o bitonic-sort-omp.o 
time ./bitonic-sort-omp.o
time mpirun -np 4 ./MPI_Merge_Gather.o 

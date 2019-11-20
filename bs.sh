mpicc biotonic-sort.c -o bs.o 
time mpirun -np 4 ./bs.o
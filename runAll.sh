gcc biotonic-sort.c -o bs.o
gcc merge-sort.c -o ms.o
gcc quick-sort.c -o qs.o
time ./bs.o
time ./ms.o
time ./qs.o
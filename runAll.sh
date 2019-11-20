gcc biotonic-sort.c -o bs.o
gcc biotonic-sort2.c -o bs2.o
gcc merge-sort.c -o ms.o
gcc quick-sort.c -o qs.o
time ./bs2.o
time ./bs.o
time ./ms.o
time ./qs.o
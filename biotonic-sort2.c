#include<stdio.h>
#include<stdlib.h> 
#include <time.h>
#define len 1024


void ascendingSwap(int index1, int index2, int *ar) // Swap two values such that they appear in ascending order in the array
{
    if (ar[index2] < ar[index1])
    {
        int temp = ar[index2];
        ar[index2] = ar[index1];
        ar[index1] = temp;
    }
}
void decendingSwap(int index1, int index2, int *ar) // Swap two values such that they appear in decending order in the array
{
    if (ar[index1] < ar[index2])
    {
        int temp = ar[index2];
        ar[index2] = ar[index1];
        ar[index1] = temp;
    }
}
void bitonicSortFromBitonicSequence(int startIndex, int lastIndex, int dir, int *ar) // Form a increaseing or decreasing array when a bitonic input is given to the function
{
    if (dir == 1)
    {
        int counter = 0; // Counter to keep track of already swapped elements 
        int noOfElements = lastIndex - startIndex + 1;
        for (int j = noOfElements / 2; j > 0; j = j / 2)
        {
            counter = 0;
            for (int i = startIndex; i + j <= lastIndex; i++)
            {
                if (counter < j)
                {
                    ascendingSwap(i, i + j, ar);
                    counter++;
                }
                else
                {
                    counter = 0;
                    i = i + j - 1;
                }
            }
        }
    }
    else // Descending sort
    {
        int counter = 0;
        int noOfElements = lastIndex - startIndex + 1;
        for (int j = noOfElements / 2; j > 0; j = j / 2)
        {
            counter = 0;
            for (int i = startIndex; i <= (lastIndex - j); i++)
            {
                if (counter < j)
                {
                    decendingSwap(i, i + j, ar);
                    counter++;
                }
                else
                {
                    counter = 0;
                    i = i + j - 1;
                }
            }
        }
    }
}
void bitonicSequenceGenerator(int startIndex, int lastIndex, int *ar) // Generate a bitonic sequence from a random order
{
    int noOfElements = lastIndex - startIndex + 1;
    for (int j = 2; j <= noOfElements; j = j * 2)
    {
        for (int i = 0; i < noOfElements; i = i + j)
        {
            if (((i / j) % 2) == 0)
            {
                bitonicSortFromBitonicSequence(i, i + j - 1, 1, ar);
            }
            else
            {
                bitonicSortFromBitonicSequence(i, i + j - 1, 0, ar);
            }
        }
    }
}

//Funcao para printar um array
void printArray(int A[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", A[i]); 
	printf("\n"); 
} 

int main() 
{
    int *ar = (int*) malloc(len * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < len; i++)
    {
        ar[i] = rand() % (2*len) + 1;
    }

    bitonicSequenceGenerator(0, len - 1, ar);

    printf("\n--------------RESPOSTA DO BIOTONIC SORT 2-------------\n\n");
    printArray(ar,len);
}

//Adaptado daqui :
//https://gist.github.com/pranay414/2118cad8873e47dc1115e3d91d8959f9
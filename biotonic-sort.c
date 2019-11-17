#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define len 1024
#define SWAP(x,y) t = x; x = y; y = t;
    
void compare();
void bitonicmerge(int, int, int);
void recbitonic(int, int, int);
void sort();
void printArray(int*,int);
 
int arr[len];
int up = 1;
int down = 0;

int main()
{

    int i;

    //Colocando um seed baseado no tempo, assim pelo menos muda, 
    //mas, provavel que numa execucao dos 3 algoritmos fique tudo igual
    srand( time(NULL));

    for (i = 0;i < len ;i++)
    {
        arr[i] = rand() % (2*len) + 1;//2xLEN soh para ter umamaior variacao de numeros
    }

	//Para vermos o array desorganizado, soh descomentar
    /*
	printf("\n-------------------Array nao organizado--------------------\n\n"); 
	printArray(arr, len); 
    */

    sort();

    printf("\n------------Array organizado por BIOTONIC-SORT-------------\n\n"); 

    printArray(arr,len);

    return 0;
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", A[i]); 
	printf("\n"); 
} 


/*

* compare and swap based on dir

*/

void compare(int i, int j, int dir)
{
    int t;

    if (dir == (arr[i] > arr[j]))

    {

        SWAP(arr[i], arr[j]);

    }
}

/*

* Sorts a bitonic sequence in ascending order if dir=1
* otherwise in descending order

*/

void bitonicmerge(int low, int c, int dir)
{
    int k, i;

    if (c > 1)
    {
        k = c / 2;

        for (i = low;i < low+k ;i++)

            compare(i, i+k, dir);    

            bitonicmerge(low, k, dir);

            bitonicmerge(low+k, k, dir);    
    }
}

/*

* Generates bitonic sequence by sorting recursively
* two halves of the array in opposite sorting orders
* bitonicmerge will merge the resultant arr

*/

void recbitonic(int low, int c, int dir)
{
    int k;

    if (c > 1)
    {
        k = c / 2;

        recbitonic(low, k, up);

        recbitonic(low + k, k, down);

        bitonicmerge(low, c, dir);
    }
}

/*

* Sorts the entire array

*/

void sort()
{
    recbitonic(0, len, up);
}
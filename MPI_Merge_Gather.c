#include<stdio.h>
#include<stdlib.h> 
#include <time.h>
#include "mpi.h"
#define len 1024
#define verbose 0
#define showResult 0

//Para a  explicacao  do codigo pense que nosso array desarrumado eh
// 3 1 8 2 5 6 4 7  

// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(int arr[], int l, int m, int r) 
{ 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 = r - m; 

	int L[n1], R[n2]; 

	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1+ j]; 

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2) 
	{ 
		if (L[i] <= R[j]) 
		{ 
			arr[k] = L[i]; 
			i++; 
		} 
		else
		{ 
			arr[k] = R[j]; 
			j++; 
		} 
		k++; 
	} 

	/* Copy the remaining elements of L[], if there 
	are any */
	while (i < n1) 
	{ 
		arr[k] = L[i]; 
		i++; 
		k++; 
	} 

	/* Copy the remaining elements of R[], if there 
	are any */
	while (j < n2) 
	{ 
		arr[k] = R[j]; 
		j++; 
		k++; 
	} 
} 

//Esquerda e direitado subarray a ser ordenado
void mergeSort(int arr[], int l, int r) 
{ 
	if (l < r) 
	{ 
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l+(r-l)/2; 

		// Sort first and second halves 
		mergeSort(arr, l, m); 
		mergeSort(arr, m+1, r); 

		merge(arr, l, m, r); 
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

int main(int argc,char** argv) 
{ 
    int meu_rank,np,tag=0;
	int from,to=0;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&meu_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&np);

    int i;
    int *arr = (int*) malloc (len*sizeof(int));


    //---------------------Criando o Array a ser Ordenado

    //Colocando um seed baseado no tempo, assim pelo menos muda, 
    //mas, provavel que numa execucao dos 3 algoritmos fique tudo igual
    srand( time(NULL));

    for ( i = 0; i < len; i++)
    {
        arr[i]= rand() % (2*len) + 1; //2xLEN soh para ter umamaior variacao de numeros
    }
    
    if(verbose){
        printf("\n-------------------Array nao organizado--------------------\n\n");  
        printArray(arr, len); 
    }

    int subLen = len/np;
    int *subArr = (int*) malloc (subLen*sizeof(int));

    MPI_Scatter(arr,
                subLen,
                MPI_INT,
                subArr,
                subLen,
                MPI_INT,
                0,
                MPI_COMM_WORLD);



    if(verbose){
        printf("\n------Sou o processo %d , e este eh meu SubArray :  \n\n",meu_rank);
        printArray(subArr, subLen);
    }

    //----------------Sorting

	mergeSort(subArr, 0, (subLen-1)); 

    int *arrSorted = (int*) malloc (len*sizeof(int));

    MPI_Gather(subArr,
        subLen,
        MPI_INT,
        arrSorted,
        subLen,
        MPI_INT,
        0,
        MPI_COMM_WORLD);

    if(meu_rank==0){
        mergeSort(arrSorted,0,len-1);

        if(showResult){
            printf("\n-------------------RESULTADO----------------\n\n");
            printArray(arrSorted,len);
        }
    }

    free(arrSorted);
    
    free(arr);
    free(subArr);

    //printf("\nMeu Rank :%d\n",meu_rank);

    MPI_Barrier(MPI_COMM_WORLD);

	MPI_Finalize();

	return 0; 
} 




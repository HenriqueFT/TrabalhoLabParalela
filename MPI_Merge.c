#include<stdio.h>
#include<stdlib.h> 
#include <time.h>
#include "mpi.h"
#define len 1024
#define verbose 0
#define showResult 1

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

	/* create temp arrays */
	int L[n1], R[n2]; 

	/* Copy data to temp arrays L[] and R[] */
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


/* l is for left index and r is right index of the 
sub-array of arr to be sorted */
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

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++) 
		printf("%d ", A[i]); 
	printf("\n"); 
} 


int * partialMergeSort(int meu_rank,int arr1[],int arr2[],int semiL,int target[],int l, int r){
    int fullL = semiL*2;
    int i;
    int k=0;
    for (i = 0; i < semiL; i++)
    {
        target[k]=arr1[i];
        k++;
    }
    //k vai estar no valor de semiL que eh o inicio do seguinte.
    for (i = 0; i < semiL; i++)
    {
        target[k]=arr2[i];
        k++;
    }
    
    if(verbose){
        printf("\n-----specialMerge atual (%d)-------\n\n",meu_rank);
        printArray(target,fullL);
    }

    mergeSort(target,l,r);

    return target;
}

/* Driver program to test above functions */
int main(int argc,char** argv) 
{ 

    int meu_rank,np,tag=0;
	int from,to=0;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&meu_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&np);


    int *arr = (int*) malloc(len*sizeof(int));

    if(meu_rank==0){
        //arr = (int*) malloc(len*sizeof(int));

        //---------------------Criando o Array a ser Ordenado

        //Colocando um seed baseado no tempo, assim pelo menos muda, 
        //mas, provavel que numa execucao dos 3 algoritmos fique tudo igual
        srand( time(NULL));
        int i;
        for ( i = 0; i < len; i++)
        {
            arr[i]= rand() % (2*len) + 1; //2xLEN soh para ter umamaior variacao de numeros
        }
        
        if(verbose){
            printf("\n-------------------Array nao organizado--------------------\n\n");  
            printArray(arr, len); 
        }

       //-------------------Enviando o array gerado----------------------
       //Pode se utilizar o MPI_SCATTER queele ja manda tudo dividido 
       //OU o MPI_Bcast soh para mandar tudo de uma vez

       MPI_Send(arr,
                len,
                MPI_INT,
                1,
                tag,
                MPI_COMM_WORLD);
       MPI_Send(arr,
                len,
                MPI_INT,
                2,
                tag,
                MPI_COMM_WORLD);
       MPI_Send(arr,
                len,
                MPI_INT,
                3,
                tag,
                MPI_COMM_WORLD);
       
    }else{

        MPI_Recv(arr,
                len,
                MPI_INT,
                0,  
                tag,
                MPI_COMM_WORLD,
                &status);
    }

    //Observacao Mergesort eh O(n) quando o array esta organizado, 
    //entao dividir em 4 arrays acelera bem.

    //---------------Dividindo o array
    int subLen = len/np;
    int *subArr = malloc(subLen *sizeof(int));

    int start=meu_rank*subLen; 
    int end=start+subLen-1;     //Termina na ultima posicao especificamente (array de tamanho 7 o end eh 6)

    int k=0;
    int i;
    for ( i = start; i <= end; i++)
    {
        subArr[k]=arr[i];
        k++;
    }
   
    /*Essas serao os sub arrays desorganizados:
    Processo 0 : 3 1 
    Processo 1 : 8 2 
    Processo 2 : 5 6
    Processo 3 : 4 7
    */
   
    if(verbose){
        printf("\n------Sou o processo %d , e este eh meu SubArray :  \n\n",meu_rank);
        printArray(subArr, subLen);
    }

    //----------------Sorting

	mergeSort(subArr, start, end); 

    /*
	printf("\n--------------Array organizado por MERGE-SORT ( %d )--------------\n\n",meu_rank); 
	printArray(subArr, subLen);
    */
    /*
    Essas serao os sub arrays desorganizados:
    Processo 0 : 1 3
    Processo 1 : 2 8
    Processo 2 : 5 6
    Processo 3 : 4 7
    */

    //----------------Juntando os resultados parciais


    //-------------Pegaremos o 1/4 do array do processo 1 e do 3 e faremos merge desses, 
    //-------------assim como seria em um merge sort
    int mergeLen = subLen*2;
    int *mergeArr=NULL;
    int *tempArr=NULL;
    if(meu_rank==0 || meu_rank==2){
        tempArr = malloc (subLen* sizeof(int)); // guardara o subArr do 1 e do 3
        mergeArr = malloc (mergeLen* sizeof(int));
        int sender= meu_rank+1; // 0->1 & 2->3
        MPI_Recv(tempArr,
                subLen,
                MPI_INT,
                sender,  
                tag,
                MPI_COMM_WORLD,
                &status);

        /*
        Rank 0 tem |1 3| e |2 8|
        Rank 2 tem |5 6| e |4 7| 

        Faremos Merge de ambos  l=0 m=r/2 r=mergeLen-1=4-1=3
        */
        int l = 0; 
        int r = mergeLen-1;

        mergeArr = partialMergeSort(meu_rank,subArr,tempArr,subLen,mergeArr,l,r);

        if(verbose){
            printf("\n--Resultado ateh agora (%d)---\n\n",meu_rank);
            printArray(mergeArr,mergeLen);
        }

    }else{//rank 1 e 3
        int target = meu_rank-1; //1<-0 & 3<-2
        MPI_Send(subArr,
                subLen,
                MPI_INT,
                target,
                tag,
                MPI_COMM_WORLD);
    }


    //--------------Pegaremos os dois 1/2 que sobraram e uniremos eles

    if(meu_rank==2){
        MPI_Send(mergeArr,
                mergeLen,
                MPI_INT,
                0,
                tag,
                MPI_COMM_WORLD);
    } 

    if(meu_rank==0){
        int *tempMergedArr = (int*) malloc (mergeLen* sizeof(int));//Armazena o mergeArr do 2
        int *arrSorted = (int*) malloc (len *sizeof(int));//irah armazenar o vetor ordenado.
        
        MPI_Recv(tempMergedArr,
                mergeLen,
                MPI_INT,
                2,  
                tag,
                MPI_COMM_WORLD,
                &status);
        
        
        /*
        Rank 0 tem |1 2 3 8| e |4 5 6 7|

        Faremos Merge de ambos  l=0 m=r/2 r=len-1=8-1=7
        */
        int l = 0;
        int r = len-1;

        arrSorted = partialMergeSort(meu_rank,mergeArr,tempMergedArr,mergeLen,arrSorted,l,r);

        if(showResult){
            printf("\n***********************************************************\n");
            printf("\n**********************Resultado Final**********************\n");
            printArray(arrSorted,len);
            printf("\n***********************************************************\n");
        }


        free(tempMergedArr);
        free(arrSorted);
    }

    if(meu_rank==0 || meu_rank==2){free(tempArr);free(mergeArr);}
    
    free(subArr);
    free(arr);
    MPI_Barrier(MPI_COMM_WORLD);

	MPI_Finalize();

	return 0; 
} 

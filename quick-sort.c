#include<stdio.h> 
#include <stdlib.h>
#include <time.h>
#define len 1024
  
// A utility function to swap two elements 
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
  
/* This function takes last element as pivot, places 
   the pivot element at its correct position in sorted 
    array, and places all smaller (smaller than pivot) 
   to left of pivot and all greater elements to right 
   of pivot */
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (arr[j] < pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
  
/* The main function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 
  
/* Function to print an array */
void printArray(int arr[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
} 
  
// Driver program to test above functions 
int main() 
{ 
    int i;

    int arr[len];

    //Colocando um seed baseado no tempo, assim pelo menos muda, 
    //mas, provavel que numa execucao dos 3 algoritmos fique tudo igual
    srand( time(NULL)); 

    for ( i = 0; i < len; i++)
    {
        arr[i]= rand() % (2*len) + 1; //2xLEN soh para ter umamaior variacao de numeros
    }
    
	//Para vermos o array desorganizado, soh descomentar
	/*
	printf("\n-------------------Array nao organizado--------------------\n\n");  
	printArray(arr, len); 
	*/

    quickSort(arr, 0, len-1);
    
	printf("\n--------------Array organizado por QUICK-SORT--------------\n\n"); 

    printArray(arr, len); 

    return 0; 
} 

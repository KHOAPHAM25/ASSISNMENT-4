#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
  //if l us equal are greater than r 
    if (l >= r) return;
  //this is mid to 1 plus r divided by 2
    int mid = (l + r) / 2;
  //mergesort
    mergeSort(pData, l, mid);
  //mergesort
    mergeSort(pData, mid + 1, r);
  //int temp to size of malloc
    int* tmp = (int*) malloc(sizeof(int) * (r - l + 1));
  //extraMemory that us allocated
    extraMemoryAllocated += sizeof(int) * (r - l + 1);
  //int l to l, j is to mid plus 1
    int i = l, j = mid + 1, k = 0;
  //while is mid and j is less than or equal to r
    while (i <= mid && j <= r) {
      //if pData is less than pData
        if (pData[i] < pData[j]) tmp[k++] = pData[i++];
          //all else tmp k++ is pData j++
        else tmp[k++] = pData[j++];
    }
  //while i is less than or equal to mid 
    while (i <= mid) tmp[k++] = pData[i++];
  //while j is less than r or equal to r 
    while (j <= r) tmp[k++] = pData[j++];
  //for i to l, i is less than r or equal to r, i plus 1
    for (int i = l; i <= r; i++) pData[i] = tmp[i - l];
  //free the temp
    free(tmp);
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
  // for int i to 1, i is less than n, and i plus 1
    for (int i = 1; i < n; i++) {
      //int key to pData i
        int key = pData[i];
      //int j to i minus 1
        int j = i - 1;
      //while j is less than or equal to 0 and pDaya j is less greater
        while (j >= 0 && pData[j] > key) {
          // pData plus 1 to pData J 
            pData[j + 1] = pData[j];
          //j minus 1
            j--;
        }
      //pData j plus 1 to key
        pData[j + 1] = key;
    }
  //extraMemory Allocated to 0
    extraMemoryAllocated = 0;
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
  //int swapped is 1
    int swapped = 1;
  //for int i is 0, i is less than n minus 1, and i plus 1
    for (int i = 0; i < n - 1 && swapped; i++) {
      //swapped to 0 
        swapped = 0;
      // int j is 0, j is less than n minus 1 minus i, j is plus 1
        for (int j = 0; j < n - 1 - i; j++) {
          //if pData j is greaer than pData plus 1 
            if (pData[j] > pData[j + 1]) {
              //int temp to pData j 
                int tmp = pData[j];
              //pData j to pData plus 1
                pData[j] = pData[j + 1];
              //pData plus 1 to temp
                pData[j + 1] = tmp;
              //swapped to 1
                swapped = 1;
            }
        }
    }
  //extraMemoryAllocated to 0
    extraMemoryAllocated = 0;
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
  //in i to 0, i is less than n minus 1, i plus 
    for (int i = 0; i < n - 1; i++) {
      //int min index to i
        int minIdx = i;
      //for int j to i plus 1, j is less than, j plus 1 
        for (int j = i + 1; j < n; j++) {
          //if pData j is less than pData index to j
            if (pData[j] < pData[minIdx]) minIdx = j;
        }
      //int temp to pData I 
        int tmp = pData[i];
      //pData i to pData index
        pData[i] = pData[minIdx];
      //pData index to temp
        pData[minIdx] = tmp;
    }
  //extraMemoryAllocated to 0
    extraMemoryAllocated = 0;
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
  //open input file
    FILE* inFile = fopen(inputFileName,"r");
  //data size is 0
    int dataSz = 0;
  //data is NULL
    *ppData = NULL;
//if inFile
    if (inFile)
    {
      //scan file
        fscanf(inFile,"%d\n",&dataSz);
      //ppData to int mallac size 
        *ppData = (int *)malloc(sizeof(int) * dataSz);
      //i standards
        for (int i = 0; i < dataSz; i++) {
          //read file
            fscanf(inFile, "%d", &(*ppData)[i]);
        }
      //close the file
        fclose(inFile);
    }
//return the datasize
    return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
  //int i, size is 100
	int i, sz = dataSz - 100;
  //print Data
	printf("\tData:\n\t");
  //i standards
	for (i=0;i<100;++i)
	{
    //print out the numbers 
		printf("%d ",pData[i]);
	}
  //print down
	printf("\n\t");
//i to size is less than data size
	for (i=sz;i<dataSz;++i)
	{
    //print out the pData
		printf("%d ",pData[i]);
	}
  //tab down 
	printf("\n\n");
}
//this is the main void
int main(void)
{
  //clock t start and end which run time
	clock_t start, end;
  //int i initialized
	int i;
  //cpu used
    double cpu_time_used;
  //open the input files
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
//i standards
	for (i=0;i<3;++i)
	{
    //int data
		int *pDataSrc, *pDataCopy;
    //data size is pased 
		int dataSz = parseData(fileNames[i], &pDataSrc);
// IF dataSz to 0
		if (dataSz <= 0)
			continue;
//copy size of the data
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
// print the line
		printf("---------------------------\n");
    //print the Data Size
		printf("Dataset Size : %d\n",dataSz);
    //print the line
		printf("---------------------------\n");
//print Selection Sort
		printf("Selection Sort:\n");
    //copy data
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
    //extraMemory Allocated to 0
		extraMemoryAllocated = 0;
    //start the clock
		start = clock();
    //selection sort
		selectionSort(pDataCopy, dataSz);
    //end the clock 
		end = clock();
    //cpu time used 
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    //print the runtime
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
    //print the extra memory allocated 
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
    //print the array
		printArray(pDataCopy, dataSz);
//print insertion sort
		printf("Insertion Sort:\n");
    //copy the data
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
    //extraMemoryAllocated to 0 
		extraMemoryAllocated = 0;
    //start clock
		start = clock();
    //insertionsort for data copy and size
		insertionSort(pDataCopy, dataSz);
    //clock end
		end = clock();
    //cpu time used 
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    //print run time
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
    //print extra memory allocated 
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
    //print array of datacopy and size
		printArray(pDataCopy, dataSz);
//print the bubblesort 
		printf("Bubble Sort:\n");
    //copy 
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
    //extraMemoryAllocated to 0
		extraMemoryAllocated = 0;
    // start clock 
		start = clock();
    //bubble sort 
		bubbleSort(pDataCopy, dataSz);
    //end clock
		end = clock();
    //cpu time used
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    //print runtime
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
    //print extra memory allocated 
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
    //print DataCopy and data size
		printArray(pDataCopy, dataSz);
//print merge sort
		printf("Merge Sort:\n");
    //copy data
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
    //extraMemoryAllocated to 0 
		extraMemoryAllocated = 0;
    //start clock 
		start = clock();
    //merge sort 
		mergeSort(pDataCopy, 0, dataSz - 1);
    //end clock 
		end = clock();
    //cpu time used 
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    //print runtime
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
    //print extra memory allocated 
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
    //print array
		printArray(pDataCopy, dataSz);
//free DataCopy
		free(pDataCopy);
    //free pDaraSrc
		free(pDataSrc);
	}

}

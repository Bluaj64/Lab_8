#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

//Helps Heap Sort by turning binary tree into a Max-heap
void heapify(int pData[], int n, int i) 
{
  int largest, leftNode, rightNode, temp;
  largest = i;
  leftNode = (2 * i + 1);
  rightNode = (2 * i + 2);

  if (leftNode < n && pData[leftNode] > pData[largest])
  {
    largest = leftNode;
  }

  if (rightNode < n && pData[rightNode] > pData[largest])
  {
    largest = rightNode;
  }
    

    if (largest != i) 
	{

	  temp = pData[i];
	  pData[i] = pData[largest];
	  pData[largest] = temp;

      heapify(pData, n, largest);

  	}

}


// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int pData[], int n)
{
	int temp;
	for (int i = (n/2 - 1); i >= 0; i--)
	{
		heapify(pData, n, i);
	}

	for (int i = n -1; i >= 0; i--)
	{
		temp = pData[0];
	  	pData[0] = pData[i];
	  	pData[i] = temp;

		heapify(pData, i, 0;);
	}

}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if (r > l)
  {
	 int mid_pt = ((l+r)/2);
    mergeSort(pData, l, mid_pt);
    mergeSort(pData, (mid_pt+1), r);
   
    //merge:
    int a, b, c;
    int tmp_size = mid_pt - l + 1;
    int tmp_size2 = r - mid_pt;
  
    int *tmp1 = (int*) malloc(tmp_size * sizeof(int));
	extraMemoryAllocated += tmp_size * sizeof(int);
    int *tmp2 = (int*) malloc(tmp_size2 * sizeof(int));
	extraMemoryAllocated += tmp_size2 * sizeof(int);
  
    for (a = 0; a < tmp_size; a++)
      {
        tmp1[a] = pData[l + a];
      }
    
    for (b = 0; b < tmp_size2; b++)
      {
        tmp2[b] = pData[(mid_pt + 1) + b];
      }
    
    a = 0; 
    b = 0; 
    c = l; 
    while (a < tmp_size && b < tmp_size2)
    {
      if (tmp1[a] <= tmp2[b])
        {
          pData[c] = tmp1[a];
          a++;
        }
      else
        {
          pData[c] = tmp2[b];
          b++;
        }
      c++;
    }
    
    while (a < tmp_size)
    {
      pData[c] = tmp1[a];
      a++;
      c++;
    }
    
    while (b < tmp_size2)
    { 
      pData[c] = tmp2[b];
      b++;
      c++;
    }
    free(tmp1);
    free(tmp2);
  }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}
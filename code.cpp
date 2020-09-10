#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* structure for passing data to threads */
typedef struct{
    
    int row;
    int column;
    
}parameters;

//for time
clock_t start, end;
double cpu_time_used;

double time_arr[11];


void *col_runner(void *param); 	
void *row_runner(void *param);
void *subgrid_runner(void *param);

//void insertionSort(int* array[], int n);// Insertion Sort Function


int puzzle [9][9];
int check [11];//array for threads returnings
int k=0;//index for check

pthread_t T1;//for columns
pthread_t T2;//for rows

pthread_t T00;//for the top left 3×3 subgrid
pthread_t T03;//for the top middle 3×3 subgrid
pthread_t T06;//for the top right 3×3 subgrid

pthread_t T30;
pthread_t T33;
pthread_t T36;

pthread_t T60;
pthread_t T63;
pthread_t T66;






int main(int argc, char *argv[])
{
	
	FILE *sudoku_file; 
	sudoku_file = fopen("testcase01.txt", "r");
    if (sudoku_file == NULL) 
    { 
        printf("Value of errno: %d\n", errno); 
        printf("Error opening the file: %s\n", strerror(errno)); 

  
        exit(EXIT_FAILURE); 
    } 	
	
	int i,j;
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++){
			fscanf(sudoku_file, "%d ", &puzzle[i][j]);
		}
	}		
	
	
	//time_t start = time(NULL);//start time
		
	parameters *data1 = (parameters *) malloc(sizeof(parameters));//for columns
	data1->row = 0;
	data1->column = 0;
	pthread_create(&T1, NULL, col_runner, (void *) data1);
	
	parameters *data2 = (parameters *) malloc(sizeof(parameters));//for rows
	data2->row = 0;
	data2->column = 0;
	pthread_create(&T2, NULL, row_runner, (void *) data2);
	
	
	parameters *data00 = (parameters *) malloc(sizeof(parameters));//for subgrids
	data00->row = 0;
	data00->column = 0;
	pthread_create(&T00, NULL, subgrid_runner, (void *) data00);

	parameters *data03 = (parameters *) malloc(sizeof(parameters));
	data03->row = 0;
	data03->column = 3;
	pthread_create(&T03, NULL, subgrid_runner, (void *) data03);

	parameters *data06 = (parameters *) malloc(sizeof(parameters));
	data06->row = 0;
	data06->column = 6;
	pthread_create(&T06, NULL, subgrid_runner, (void *) data06);
		
	parameters *data30 = (parameters *) malloc(sizeof(parameters));
	data30->row = 3;
	data30->column = 0;
	pthread_create(&T30, NULL, subgrid_runner, (void *) data30);
	
	parameters *data33 = (parameters *) malloc(sizeof(parameters));
	data33->row = 3;
	data33->column = 3;
	pthread_create(&T33, NULL, subgrid_runner, (void *) data33);
	
	parameters *data36 = (parameters *) malloc(sizeof(parameters));
	data36->row = 3;
	data36->column = 6;
	pthread_create(&T36, NULL, subgrid_runner, (void *) data36);
	
	parameters *data60 = (parameters *) malloc(sizeof(parameters));
	data60->row = 6;
	data60->column = 0;
	pthread_create(&T60, NULL, subgrid_runner, (void *) data60);
	
	parameters *data63 = (parameters *) malloc(sizeof(parameters));
	data63->row = 6;
	data63->column = 3;
	pthread_create(&T63, NULL, subgrid_runner, (void *) data63);
	
	parameters *data66 = (parameters *) malloc(sizeof(parameters));
	data66->row = 6;
	data66->column = 6;
	pthread_create(&T66, NULL, subgrid_runner, (void *) data66);
	
	
	pthread_join(T1, NULL);
	printf("thread 1:\t%lf s\n",time_arr[0]);
    pthread_join(T2, NULL);
	printf("thread 2:\t%lf s\n",time_arr[1]);    
    pthread_join(T00, NULL);
	printf("thread 3:\t%lf s\n",time_arr[2]);  
    pthread_join(T03, NULL);
	printf("thread 4:\t%lf s\n",time_arr[3]);  
    pthread_join(T06, NULL);
	printf("thread 5:\t%lf s\n",time_arr[4]);  
    pthread_join(T30, NULL);
	printf("thread 6:\t%lf s\n",time_arr[5]);  
	pthread_join(T33, NULL);
	printf("thread 7:\t%lf s\n",time_arr[6]);  
    pthread_join(T36, NULL);
	printf("thread 8:\t%lf s\n",time_arr[7]);  
    pthread_join(T60, NULL);
	printf("thread 9:\t%lf s\n",time_arr[8]);  
    pthread_join(T63, NULL);
	printf("thread 10:\t%lf s\n",time_arr[9]);  
    pthread_join(T66, NULL);	
	printf("thread 11:\t%lf s\n",time_arr[10]);  
	

	
	int z;
	int flag = 1;
	for(z=0; z<11; z++)
	{
		
		if(check[z] == 0)
		{			
			printf("result: Not a valid solution\n");
			return 0;
		}

	}
	

	printf("\n\nresult: valid solution\n");

}


void insertionSort(int *array, int n) 
{ 
	//printf("insertion\n");
    int i, element, j; 
    for (i = 1; i < n; i++) 
		{ element = array[i]; 
			j = i - 1;
			while (j >= 0 && array[j] > element) 
			{ 
            	array[j + 1] = array[j]; 
            	j = j - 1; 
        } 
        array[j + 1] = element; 
    } 
} 



void *col_runner(void *param)
{


	start = clock();

	
	parameters * Col = (parameters *) param;
	int myCol = Col->column;
	int myRow = Col->row;
	
	
	int checkCol[9];
	
	int arr[9];//for storing the elements of the column and sorting them
	
	int i,j,t;
	for(i=myCol; i<9 ;i++)
	{	
		for(t=0;t<9;t++)
		{		
			arr[t] = puzzle[i][t];
		}
		
		insertionSort(arr,9);//sorting the column
	
		int flag=1;
		for(j=0; j<9; j++)//comparing the sorted array with array containing 1 to 9 respectively
		{
			if(arr[j] != (j+1))
				flag = 0;				
		}
		

		checkCol[i] = flag;

			
	}
	
	int m;
	for(m=0 ; m<9;m++)
	{	
		if(checkCol[m] == 0)
			check[k] = 0;
	}
	
	check[k]=1;

	k++;
	
	

	end = clock();
    cpu_time_used = ((double) (end - start)) / (double)CLOCKS_PER_SEC;
    time_arr[0] = cpu_time_used;
    //printf("thread1:\t%lf s\n",cpu_time_used);
	
	pthread_exit(0);
}



void *row_runner(void *param)
{
	
	start = clock();
	
	
	
	parameters * Row = (parameters *) param;
	int myCol = Row->column;
	int myRow = Row->row;

	
	int checkRow[9];
	
	int arr[9];//for storing the elements of the column and sorting them
	
	int i,j,t;
	for(i=myRow; i<9 ;i++)
	{	
		for(t=0;t<9;t++)
		{		
			arr[t] = puzzle[i][t];
		}
		
		insertionSort(arr,9);//sorting the column

		int flag=1;
		for(j=0; j<9; j++)//comparing the sorted array with array containing 1 to 9 respectively
		{
			if(arr[j] != (j+1))
				flag = 0;				
		}
		


		checkRow[i] = flag;

	}
	
	int m;
	for(m=0 ; m<9;m++)
	{	
		if(checkRow[m] == 0)
			check[k] = 0;
	}
	check[k]=1;
	k++;
	
	
	end = clock();
    cpu_time_used = ((double) (end - start)) / (double)CLOCKS_PER_SEC;
    time_arr[1] = cpu_time_used;
    //printf("thread2:\t%lf s\n",cpu_time_used);
	
	pthread_exit(0);
	
	

}
void *subgrid_runner(void *param)
{
	start = clock();

	
	
	parameters * Sub = (parameters *) param;
	int myCol = Sub->column;
	int myRow = Sub->row;

	
	int arr[9];//for storing the elements of the column and sorting them
	int i,j,t,m;
	m=0;
	for(i=myRow; i<(myRow +3) ;i++)
	{
		for(j=myCol; j<(myCol+3) ;j++)
		{
			arr[m] = puzzle[i][j];
			m++;
			
		}
		
	}
	int n;

		
	
	insertionSort(arr,9);//sorting the column
	
		
	int flag=1;//asumming the sorted array contains 1 to 9
	
	for(j=0; j<9; j++)//comparing the sorted array with array containing 1 to 9 respectively
	{
		if(arr[j] != j+1)
			flag = 0;
	}
	
	check[k] = flag;

	k++;
	
	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    if(myCol == 0 && myRow == 0)
        time_arr[2] = cpu_time_used;
    if(myCol == 0 && myRow == 3)
        time_arr[3] = cpu_time_used;
	if(myCol == 0 && myRow == 6)
        time_arr[4] = cpu_time_used;
    if(myCol == 3 && myRow == 0)
        time_arr[5] = cpu_time_used;
    if(myCol == 3 && myRow == 3)
        time_arr[6] = cpu_time_used;
    if(myCol == 3 && myRow == 6)
        time_arr[7] = cpu_time_used;
	if(myCol == 6 && myRow == 0)
        time_arr[8] = cpu_time_used;	
    if(myCol == 6 && myRow == 3)
        time_arr[9] = cpu_time_used;   	
    if(myCol == 6 && myRow == 6)
        time_arr[10] = cpu_time_used;  	
    	
	pthread_exit(0);
}




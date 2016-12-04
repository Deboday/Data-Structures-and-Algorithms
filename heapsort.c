/****************************************************************************************************************************************
*																	*
*							HEAPSORT ALGORITHM								* *						      COMPLEXITY - O( NLOG(N) )						                * 
*																	*
*																	*
****************************************************************************************************************************************/


#include<stdio.h>

#define N 50

void max_heapify( int * , int , int ); // O(LOG(N))
void build_max_heap( int * , int );// 0(N)
void heap_sort( int * , int );// O(NLOG(N))
void print_array( int * , int );

int main()
{
	int arr[N];
	int i = 0 , n = 0;
	
	printf(" Enter the total no. of elements in the heap = " );
	scanf("%d" , &n );
	printf("\n Enter the elements of the heap one by one \n" );
	
	for( i = 0 ; i < n ; i++ )
		scanf("%d" , &arr[i] );
		
	heap_sort( arr , n - 1 );
	
	printf( "\n The sorted heap \n" );
	print_array( arr , n );
		
	return 0;
}

void heap_sort( int arr[] , int n )
{
	int i = 0 , h = n , temp = 0;
	build_max_heap( arr , n );
	for( i = n ; i > 0 ; i-- )
	{
		temp = arr[i];	
		arr[i] = arr[0];
		arr[0] = temp;
		h--;
		max_heapify( arr , 0 , h );
	}
}

void build_max_heap( int arr[] , int n )
{
	int i = 0;
	for( i = n / 2 ; i >= 0 ; i-- )
		max_heapify( arr , i , n );
}

void max_heapify( int arr[] , int i , int n )
{
	int l = 0 , r = 0 , largest = 0 , temp = 0;
	
	largest = i;
	l = 2 * i;
	r = 2 * i + 1;
	
	if( l <= n && arr[largest] < arr[l] )
		largest = l;
	if( r <= n && arr[largest] < arr[r] )
		largest = r;
	
	temp = arr[i];	
	arr[i] = arr[largest];
	arr[largest] = temp;
	
	if( i != largest )
		max_heapify( arr , largest , n );
}

void print_array( int arr[] , int n )
{
	for( int i = 0 ; i < n ; i++ )
		printf("%d " , arr[i] );
	printf("\n");
}


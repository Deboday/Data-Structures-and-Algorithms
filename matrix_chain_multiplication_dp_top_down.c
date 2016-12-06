#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define N 50

int optimal_solution( int (*)[N+1] , int (*)[N+1] , int * , int , int );
void print_optimal_solution( int (*)[N+1] , int , int );

int main()
{
	int arr[N+1][N+1] , par[N+1][N+1] , col[N+1];
	int i = 0 , n = 0;
	
	printf("Enter the total no. of matrices = " );
	scanf("%d" , &n );
	
	printf("\nEnter the total no. of rows in the first matrix = ");
	scanf("%d" , &col[0] );
	for( i = 1 ; i <= n ; i++ )
	{
		printf("\nEnter the total no. of columns in the Matrix %d = " , i );
		scanf("%d" , &col[i] );
	}
	
	for( i = 1 ; i <= n ; i++ )
		for( int j = i ; j <= n ; j++ )
			arr[i][j] = INT_MAX;
			
	printf("\nThe total no. of multiplications in the optimal solutions is %d \n" , optimal_solution( arr , par , col , 1 , n ) );
	print_optimal_solution( par , 1 , n );
	
	printf("\n");
	printf("\nThe Matrix Multiply Matrix is \n " );
	for( i = 1 ; i <= n ; i++ )
		printf( "  %d  " , i );
	printf("\n");
	for( i = 1 ; i <= n ; i++ )
	{
		printf("%d" , i );
		for( int j = 1 ; j <= n ; j++ )
		{
			if( j < i )
				printf( "     " );
			else
				printf( "  %d  " , arr[i][j] );
		}
		printf("\n");
	}
	
	printf("\nThe Partition Matrix is \n " );
	for( i = 1 ; i <= n ; i++ )
		printf( "  %d  " , i );
	printf("\n");
	for( i = 1 ; i <= n ; i++ )
	{
		printf("%d" , i );
		for( int j = 1 ; j <= n ; j++ )
		{
			if( j <= i )
				printf( "     " );
			else
				printf( "  %d  " , par[i][j] );
		}
		printf("\n");
	}
	return 0;
}

int optimal_solution( int arr[][N+1] , int par[][N+1] , int col[] , int i , int j )
{
	int max = 0 , max1 = 0;
	if( i == j )
	{
		arr[i][i] = 0;
		return 0;
	}
	if( arr[i][j] != INT_MAX )
		return arr[i][j];
		
	for( int k = i ; k < j ; k++ )
	{
		max = optimal_solution( arr , par , col , i , k );
		max1 = optimal_solution( arr , par , col , k + 1 , j );
		
		if( arr[i][j] > max + max1 + col[i-1]*col[k]*col[j] )
		{
			arr[i][j] = max + max1 + col[i-1]*col[k]*col[j];
			par[i][j] = k;
		}
	}
	return arr[i][j];
}

void print_optimal_solution( int par[][N+1] , int i , int j )
{
	if( i == j )
		printf( " M%d " , i );
	else
	{
		printf("(");
		print_optimal_solution( par , i , par[i][j] );
		print_optimal_solution( par , par[i][j] + 1 , j );
		printf(")");
	}
}

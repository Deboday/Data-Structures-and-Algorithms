#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

#define N 100

void warshall( int (*)[] , int );

int main()
{
	int weight[N][N];
	int n = 0;
	printf("Enter the total no. of Vertices = " );
	scanf("%d" , &n );
	printf("\nIf there is a edge between the pair of vertices enter 1. Else 0" );
	for( int i = 0 ; i < n ; i++ )
	{
		for( int j = 0 ; j < n ; j++ )
		{
			printf("\nEnter the weight of the edge between %d and %d = " , i , j );
			scanf("%d" , &weight[i][j] );
		}
	}
	printf("\nThe path Matrix is. 1 if there is a path . 0 if no path\n");
	warshall( weight , n );
	for( int i = 0 ; i < n ; i++ )
	{
		for( int j = 0 ; j < n ; j++ )
		{
			printf("  %d  " , weight[i][j] );
		}
		printf("\n");
	}
	return -1;
}

void warshall( int weight[][N] , int n )//O(V^3)
{		
	for( int k = 0 ; k < n ; k++ )
	{
		for( int i = 0 ; i < n ; i++ )
		{
			for( int j = 0 ; j < n ; j++ )
			{
				if( i != j )
				{
					weight[i][j] = weight[i][j] | ( weight[i][k] & weight[k][j] );
				}
			}			
		}
	}
}

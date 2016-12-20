#include<stdio.h>
#include<limits.h>
#include<stdlib.h>

#define N 100

void floyd_warshall( int (*)[] , int (*)[] , int );
void print_path( int (*)[] , int , int );

int main()
{
	int weight[N][N] , predecessor[N][N];
	int n = 0;
	printf("Enter the total no. of Vertices = " );
	scanf("%d" , &n );
	printf("\nIf there is a edge between the pair of vertices enter its weight. Else 0" );
	for( int i = 0 ; i < n ; i++ )
	{
		for( int j = 0 ; j < n ; j++ )
		{
			printf("\nEnter the weight of the edge between %d and %d = " , i , j );
			scanf("%d" , &weight[i][j] );
			predecessor[i][j] = i;
			if( weight[i][j] == 0 && i != j )
				weight[i][j] = INT_MAX;
		}
	}
	printf("\n");
	floyd_warshall( weight , predecessor , n );
	for( int i = 0 ; i < n ; i++ )
	{
		for( int j = 0 ; j < n ; j++ )
		{
			if( i != j && weight[i][j] != INT_MAX )
			{			
				printf("Shortest path between %d and %d = %d. The path is " , i , j , weight[i][j] );
				print_path( predecessor , i , j );
				printf("\n");
			}
			else
				printf( "No Path between %d and %d \n" , i , j );
		}
	}
	return -1;
}

void floyd_warshall( int weight[][N] , int predecessor[][N] , int n )//O(V^3)
{		
	for( int k = 0 ; k < n ; k++ )
	{
		for( int i = 0 ; i < n ; i++ )
		{
			for( int j = 0 ; j < n ; j++ )
			{
				if(i != j && weight[i][k] != INT_MAX && weight[k][j] != INT_MAX && weight[i][j] > weight[i][k]+ weight[k][j])
				{
					weight[i][j] = weight[i][k] + weight[k][j];
					predecessor[i][j] = predecessor[k][j];
				}
			}			
		}
	}
}

void print_path( int predecessor[][N] , int i , int j )
{
	if( i == j )
		printf( " %d " , i );
	else
	{
		print_path( predecessor , i , predecessor[i][j] );
		printf( " %d " , j );
	}
}
					
				

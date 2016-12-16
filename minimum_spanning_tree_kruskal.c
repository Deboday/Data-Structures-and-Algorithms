#include<stdio.h>
#include<stdlib.h>

#define N 100

typedef struct edge
		  {	
		  	int length;
		  	int start_vertex;
		  	int end_vertex;
		  }Edge;
		  
		  
void mst_kruskal( Edge * , int , int );
void make_set( int * , int );
int find_set( int * , int );	
void union_set( int * , int , int );	
int cmpfnc( const void * , const void * );
		  

int main()
{
	int n = 0 , i = 0;
	Edge arr[N];
	printf( "Enter the total no. of vertices in the graph = " );
	scanf( "%d" , &n );
	printf( "\nEnter the edges of the Graph. When done press -1 when told to enter the vertex\n" );
	while(1)
	{
		printf( "Enter the vertex = " );
		scanf( "%d" , &arr[i].start_vertex );
		if( arr[i].start_vertex == -1 )
			break;
		printf( "Enter the adjacent vertex = " );
		scanf( "%d" , &arr[i].end_vertex );	
		printf( "Enter the length between vertex %d and %d = " , arr[i].start_vertex , arr[i].end_vertex );
		scanf( "%d" , &arr[i].length );	
		i++;	
	}
	mst_kruskal( arr , i , n );
	return -1;
}

void mst_kruskal( Edge arr[] , int i , int n )//O(ELOG(V))
{
	int ver[n];
	Edge mst[n-1];
	make_set( ver , n );
	int k = 0 , j = 0;
	while( k < i )
	{
		if( find_set( ver , arr[k].start_vertex ) != find_set( ver , arr[k].end_vertex ) )
		{
			union_set( ver , arr[k].start_vertex , arr[k].end_vertex );
			mst[j] = arr[k];
			j++;
		}
		k++;
	}
	if( j != n - 1 )
	{
		printf( "\nThe Graph is a disconnected graph and hence no Minimum Spanning Tree\n" );
		return;
	}
	printf( "\nThe Edges in the Minimum Spanning Tree are :- \n" );
	while( j >= 0 )
	{
		j--;
		printf( " Vertex %d to Vertex %d of length %d \n" , mst[j].start_vertex , mst[j].end_vertex , mst[j].length );
	}
}

void make_set( int ver[] , int n )
{
	for( int i = 0 ; i < n ; i++ )
		ver[i] = i;
}

int find_set( int ver[] , int i )
{
	while( ver[i] != i )
		i = ver[i];
	return i;
}

void union_set( int ver[] , int i , int j )
{
	ver[find_set(ver,j)] = find_set(ver,i); 
}

int cmpfnc( const void * a , const void * b )
{
	return ((Edge *)a)->length - ((Edge *)b)->length;
}



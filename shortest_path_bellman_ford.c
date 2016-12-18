#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define N 100

#define true 1
#define false 0

typedef int boolean;

typedef struct edge
		  {	
		  	int length;
		  	int start_vertex;
		  	int end_vertex;
		  }Edge;
		  
typedef struct vertex
		  {	
		  	int parent;
		  	int distance;
		  }Vertex;
		  
void relax( Vertex * , Edge );
void initialize_shortest_path( Vertex * , int , int );
boolean bellman_ford( Edge * , int , int );

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
	
	boolean c = bellman_ford( arr , i , n );
	if( c == false )
		printf( "\nNegetive Weight Cycles are Present. Hence no Shortest Path \n" );
	return 0;
}

void relax( Vertex arr[] , Edge ab )
{
	if( arr[ab.end_vertex].distance > arr[ab.start_vertex].distance + ab.length )
	{
		arr[ab.end_vertex].distance = arr[ab.start_vertex].distance + ab.length;
		arr[ab.end_vertex].parent = ab.start_vertex;
	}
}

void initialize_shortest_path( Vertex arr[] , int n , int source )
{
	for( int i = 0 ; i < n ; i++ )
	{
		arr[i].parent = -1;
		arr[i].distance = INT_MAX;
	}
	arr[source].distance = 0;
} 

boolean bellman_ford( Edge arr[] , int a , int n )//O(VE)
{
	Vertex out[N];
	initialize_shortest_path( out , n , 0 );//O(V)
	for( int i = 0 ; i < n - 1 ; i++ )// O(V)
	{
		for( int j = 0 ; j < a ; j++ )//O(E)
		{
			relax( out , arr[j] );//O(1)  
		}
	}
	for( int i = 0 ; i < a ; i++ )//O(E) // Cheking for Negative Weight Cycles.
	{
		if( out[arr[i].end_vertex].distance > out[arr[i].start_vertex].distance + arr[i].length )
			return false;
	}
	for( int i = 0 ; i < n ; i++ )
	{
		printf( "Shortest Distance form 0 to %d is %d\n" , i , out[i].distance );
	} 
	return true;
}

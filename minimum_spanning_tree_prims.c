#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define N 100

typedef struct element
	       {
	      		int n;
	      	        int key;
	       }Object;
	      
typedef struct Priority
	       {
	       		Object arr[N];
	    		int length;
	       }QUEUE; 
	       
typedef struct edge
		  {
		  	int vertex;
		  	int weight;
		  	struct edge *next;
		  }Edge;
		  
typedef struct vertex
		    {
		    	int parent;
		    	Edge *next;
		    }Vertex;    

typedef struct graph
		   {
		   	Vertex arr[N];
		   }Graph;	   	    

void min_heap_insert( QUEUE * , int , int , int * );
Object min_heap_extract( QUEUE * , int * );
void decrease_key( QUEUE * , int , int , int * );
void min_heapify( QUEUE * , int , int , int * );

void addEdge( Graph * , int , int , int );// O(Total No. of edges adjacent to the vertex)
void buildGraph( Graph * , int );// O(V)

void mst_prims( Graph * , int , int );


int main()
{
	Graph head;
	int n = 0 , a = 0 , len = 0;
	printf("Enter the total no. of vertices = " );
	scanf("%d" , &n );
	buildGraph( &head , n );
	printf("\n Enter the edges incident on the given vertex" );
	for( int i = 0 ; i < n ; i++ )
	{
		printf("\n Enter the vertices adjacent to vertex %d and the weight of that edge. When done press -1" , i ); 
		while( 1 )
		{
			printf("\nEnter the adjacent vertex = " );
			scanf("%d" , &a );			
			if( a == -1 )
				break;
			printf("\nEnter the weight of the edge = " );
			scanf("%d" , &len );
			addEdge( &head , i , a , len );
			addEdge( &head , a , i , len ); 
		}
	}
	mst_prims( &head , 0 , n );
	return -1;
}

void mst_prims( Graph *head , int r , int n )
{
	QUEUE out;
	out.length = -1;
	Object mst[n];
	int visited[n];
	for( int i = 0 ; i < n ; i++ )
	{
		if( i != r )
			min_heap_insert( &out , i , INT_MAX , visited );
		else
			min_heap_insert( &out , i , 0 , visited );
	}
	int i = 0;
	while( out.length != -1 )
	{
		mst[i] = min_heap_extract( &out , visited );
		visited[mst[i].n] = -1;
		for( Edge *j = head->arr[mst[i].n].next ; j != NULL ; j = j->next )
		{
			if( visited[j->vertex] != -1 && j->weight < out.arr[visited[j->vertex]].key )
			{
				head->arr[j->vertex].parent = mst[i].n;
				decrease_key( &out , visited[j->vertex] , j->weight , visited );
			}
		}
		i++;
	}
	if( i != n )
	{
		printf("\nGraph is disconnected. No Minimum Spanning Tree \n" );
		return;
	}
	i--;
	printf("The edges in the minimum spanning tree are :- \n" );
	while( i > 0 )
	{
		printf(" Edge %d to %d of weight %d \n" , mst[i].n , head->arr[mst[i].n].parent , mst[i].key );
		i--;
	}
}

void addEdge( Graph *temp , int vertex1 , int vertex2 , int length )
{
	Edge *i = NULL;
	
	Edge *ab = ( Edge * )malloc( sizeof( Edge ) );
	ab->vertex = vertex2;
	ab->weight = length;
	ab->next = NULL;
	
	if( temp->arr[vertex1].next == NULL )
	{
		temp->arr[vertex1].next = ab;
	}
	else
	{
		for( i = temp->arr[vertex1].next ; i->next != NULL ; i = i->next );
		i->next = ab;
	}
}

void buildGraph( Graph *temp , int n )
{
	for( int i = 0 ; i < n ; i++ )
	{
		temp->arr[i].parent = -1;
		temp->arr[i].next = NULL;
	}
}


void min_heap_insert( QUEUE *head , int el , int key , int visited[] )
{
	if( head->length == N )
		return;
	Object temp = { el , key };
	head->arr[++head->length] = temp;
	visited[el] = head->length;
	decrease_key( head , head->length , key , visited );
}

Object min_heap_extract( QUEUE *head , int visited[] )
{
	Object el = head->arr[0];
	head->arr[0] = head->arr[head->length--];
	min_heapify( head , 0 , head->length , visited );
	return el;
}

void decrease_key( QUEUE *head , int index , int key , int visited[] )
{
	if( head->arr[index].key < key )
		return;
	int i = index;
	head->arr[index].key = key;
	while( i > 0 && head->arr[i/2].key > key )
	{
		visited[head->arr[i/2].n] = i;
		visited[head->arr[i].n] = i/2;
		
		Object temp = head->arr[i/2];
		head->arr[i/2] = head->arr[i];
		head->arr[i] = temp;
		i = i / 2;
	}
}

void min_heapify( QUEUE *head , int i , int n , int visited[] )
{
	int l = 0 , r = 0 , min = 0;
	
	min = i;
	l = 2 * i;
	r = 2 * i + 1;
	
	if( l <= n && head->arr[min].key > head->arr[l].key )
		min = l;
	if( r <= n && head->arr[min].key > head->arr[r].key )
		min = r;
	
	Object temp = head->arr[i];	
	head->arr[i] = head->arr[min];
	head->arr[min] = temp;
	
	visited[head->arr[min].n] = min;
	visited[head->arr[i].n] = i;
	
	if( i != min )
		min_heapify( head , min , n  , visited );
}

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
		    	int distance;
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

void djikstra( Graph * , int , int );

void initialize_shortest_path( Graph * , int , int );
void relax( Graph * , int , Edge * , QUEUE * , int * );


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
		}
	}
	djikstra( &head , 0 , n );
	return -1;
}

/********************************************************************************************************
*						COMPLEXITY 						*
*													*
*				O(ELOG(V)) = O(VLOG(V) + ELOG(V) ) = O(ELOG(V))				*
*	Best Possible is O(E + VLOG(V)) USING FIBONACCI HEAPS WHERE DECREASE_KEY TAKES O(1) TIME	*
*********************************************************************************************************/
													
void djikstra( Graph *head , int s , int n )
{
	QUEUE out;
	out.length = -1;
	int visited[n];
	initialize_shortest_path( head , n , 0 );//Useless. Can be eliminated at the time of Initializing Graph
	for( int i = 0 ; i < n ; i++ )//O(VLOG(V))
	{
		if( i != s )
			min_heap_insert( &out , i , INT_MAX , visited );
		else
			min_heap_insert( &out , i , 0 , visited );
	}
	int i = 0;
	while( out.length != -1 )//O(V)
	{
		Object ver = min_heap_extract( &out , visited );//O(LOG(V))
		visited[ver.n] = -1;
		for( Edge *j = head->arr[ver.n].next ; j != NULL ; j = j->next )//O(E)
		{
			relax( head , ver.n , j , &out , visited );//O(LOG(V))
		}
	}
	for( int i = 0 ; i < n ; i++ )
	{
		printf( "Shortest Distance form 0 to %d is %d\n" , i , head->arr[i].distance );
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

void relax( Graph *head , int u , Edge *b , QUEUE *out , int visited[] )
{
	if( visited[b->vertex] != -1 && head->arr[b->vertex].distance > head->arr[u].distance + b->weight )
	{
		head->arr[b->vertex].distance = head->arr[u].distance + b->weight;
		head->arr[b->vertex].parent = u;
		decrease_key( out , visited[b->vertex] , head->arr[b->vertex].distance , visited );
	}
}

void initialize_shortest_path( Graph *head , int n , int source )
{
	for( int i = 0 ; i < n ; i++ )
	{
		head->arr[i].parent = -1;
		head->arr[i].distance = INT_MAX;
	}
	head->arr[source].distance = 0;
} 

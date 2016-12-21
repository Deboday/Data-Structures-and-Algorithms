#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define N 50

typedef struct stack
		   {
		   	int val;
		   	struct stack *next;
		   }Stack;
		   
typedef struct edge
		  {
		  	int vertex;
		  	int length;
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

void push( Stack ** , int );// O(1)
int pop( Stack ** );// O(1)

void addEdge( Graph * , int , int , int );// O(Total No. of edges adjacent to the vertex)
void buildGraph( Graph * , int );// O(V)

void depth_first_search( Graph * , int , Stack ** , int * );// O(V+E)
void print_path( Graph , int , int );

Stack * topological_sort( Graph * , int );

void initialize_shortest_path( Vertex * , int , int );
void relax( Vertex * , int , Edge * );

void dag_shortest_path( Graph * , int );

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
		printf("\n Enter the vertices adjacent to vertex %d and their weight. When done press -1 \n" , i ); 
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
	dag_shortest_path( &head , n );	
	return -1;
}

void push( Stack **head , int value )
{
	Stack *temp = NULL;
	
	temp = ( Stack * )malloc( sizeof( Stack ) );
	
	temp->val = value;
	temp->next = *head;
	*head = temp;
}

int pop( Stack **head )
{
	Stack *temp = *head;
	int value = 0;
	
	if( temp->next == NULL )
	{
		value = temp->val;
		*head = NULL;
		free( temp );
		return value;
	}
	
	value = temp->val;
	*head = temp->next;
	free(temp);
	
	return value;
}

void addEdge( Graph *temp , int vertex1 , int vertex2 , int weight )
{
	Edge *i = NULL;
	
	Edge *ab = ( Edge * )malloc( sizeof( Edge ) );
	ab->vertex = vertex2;
	ab->length = weight;
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
		temp->arr[i].distance = -1;
		temp->arr[i].next = NULL;
	}
}

void depth_first_search( Graph *head , int start , Stack **out , int visited[] )
{
	Edge *temp = NULL;
	
	visited[start] = 1;
	
	temp = head->arr[start].next;
	while( temp != NULL )
	{
		if( visited[temp->vertex] == 0 )
		{
			head->arr[temp->vertex].parent = start;
			depth_first_search( head , temp->vertex , out , visited );
		}
		temp = temp->next;
	}
	
	push( out , start );
}

void print_path( Graph head , int start , int end )
{
	if( start == end )
		printf("  %d  " , start );
	else if( head.arr[start].parent == -1 )
		printf( "No Paths from %d to %d \n " , start , end );
	else 
	{
		print_path( head , head.arr[start].parent , end );
		printf( "  %d  " , start );
	}
}

Stack * topological_sort( Graph *head , int n )
{
	int visited[n];
	for( int i = 0 ; i < n ; i++ )
		visited[i] = 0;
	Stack *head2 = NULL;
	for( int i = 0 ; i < n ; i++ )
	{
		if( visited[i] == 0 )
		{
			depth_first_search( head , i , &head2 , visited );
		}
	}
	return head2;
}

void relax( Vertex arr[] , int u , Edge *b )
{
	if( arr[b->vertex].distance > arr[u].distance + b->length )
	{
		arr[b->vertex].distance = arr[u].distance + b->length;
		arr[b->vertex].parent = u;
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

void dag_shortest_path( Graph *head , int n )//O(V+E)
{
	Vertex out[N];
	initialize_shortest_path( out , n , 0 );//O(V)
	Stack *temp = topological_sort( head , n );//O(V+E)
	for( int i = 0 ; i < n ; i++ )//O(V)
	{
		int ver = pop(&temp);
		for( Edge *j = head->arr[ver].next ; j != NULL ; j = j->next )//O(E)
		{
			relax( out , ver , j );//O(1)
		}
	}
	for( int i = 0 ; i < n ; i++ )
	{
		printf( "Shortest Distance form 0 to %d is %d\n" , i , out[i].distance );
	}
}


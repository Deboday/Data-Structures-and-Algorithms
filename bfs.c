/****************************************************************************************************************************************
*																	*
*							BREADTH FIRST SEARCH								* *						      COMPLEXITY - O( V + E )						                * 
*																	*
*																	*
****************************************************************************************************************************************/


#include<stdio.h>
#include<stdlib.h>

#define N 50

typedef struct queue
		   {
		   	int val;
		   	struct queue *next;
		   	struct queue *end;
		   }Queue;
		   
typedef struct edge
		  {
		  	int vertex;
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

void enqueue( Queue ** , int );// O(1)
int dequeue( Queue ** );// O(1)

void addEdge( Graph * , int , int );// O(Total No. of edges adjacent to the given vertex)
void buildGraph( Graph * , int );// O(V)

void breadth_first_search( Graph * , int , int );// O(V+E)
void print_path( Graph , int , int );

int main()
{
	Graph head;
	int n = 0 , a = 0;
	printf("Enter the total no. of vertices = " );
	scanf("%d" , &n );
	buildGraph( &head , n );
	printf("\n Enter the edges incident on the given vertex" );
	for( int i = 0 ; i < n ; i++ )
	{
		printf("\n Enter the vertices adjacent to vertex %d. When done press -1 \n" , i ); 
		while( 1 )
		{
			scanf("%d" , &a );
			if( a == -1 )
				break;
			addEdge( &head , i , a );
		}
	}
	printf("\nEnter the source vertex = " );
	scanf("%d" , &a );
	breadth_first_search( &head , a , n );
	for( int i = 0 ; i < n ; i++ )
	{
		printf(" Shortest path between %d and %d is %d \n" , i , a , head.arr[i].distance );
		print_path( head , i , a );
		printf("\n");
	}
	return -1;
}

void enqueue( Queue **head , int value )
{
	Queue *temp = *head , *temp2 , *temp3 = NULL;
	
	temp2 = ( Queue * )malloc( sizeof( Queue ) );
	
	temp2->val = value;
	temp2->next = NULL;
	temp2->end = temp2;
	
	if( *head == NULL )
	{
		*head = temp2;
		return;
	}
	
	temp3 = temp->end;
	temp3->next = temp2;
	temp3->end = temp2;
	temp->end = temp2;
}

int dequeue( Queue **head )
{
	Queue *temp = *head , *temp2 = NULL;
	int value = 0;
	
	if( temp->next == NULL )
	{
		value = temp->val;
		*head = NULL;
		free( temp );
		return value;
	}
	
	temp->next->end = temp->end;
	value = temp->val;
	*head = temp->next;
	free(temp);
	
	return value;
}

void addEdge( Graph *temp , int vertex1 , int vertex2 )
{
	Edge *i = NULL;
	
	Edge *ab = ( Edge * )malloc( sizeof( Edge ) );
	ab->vertex = vertex2;
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

void breadth_first_search( Graph *head , int start , int n )
{
	Queue *head1 = NULL;
	Edge *temp = NULL;
	int a = 0;
	int visited[n];
	for( int i = 0 ; i < n ; i++ )
		visited[i] = 0;
	visited[start] = 1;
	enqueue( &head1 , start );
	while( head1 != NULL )
	{
		a = dequeue( &head1 );
		head->arr[a].distance++;
		temp = head->arr[a].next;
		while( temp != NULL )
		{
			if( visited[temp->vertex] == 0 )
			{
				enqueue( &head1 , temp->vertex );
				visited[temp->vertex] = 1;
				head->arr[temp->vertex].distance = head->arr[a].distance;
				head->arr[temp->vertex].parent = a;
			}
			temp = temp->next;
		}
	}
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
		
		
		
		
	   

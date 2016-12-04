
/****************************************************************************************************************************************
*																	*
*							DEPTH FIRST SEARCH								* *						      COMPLEXITY - O( V + E )						                * 
*																	*
*																	*
****************************************************************************************************************************************/



#include<stdio.h>
#include<stdlib.h>

#define N 50

typedef struct stack
		   {
		   	int val;
		   	struct stack *next;
		   }Stack;
		   
typedef struct edge
		  {
		  	int vertex;
		  	struct edge *next;
		  }Edge;
		  
typedef struct vertex
		    {
		    	int parent;
		    	int Time;
		    	Edge *next;
		    }Vertex;    

typedef struct graph
		   {
		   	Vertex arr[N];
		   }Graph;

void push( Stack ** , int );// O(1)
int pop( Stack ** );// O(1)

void addEdge( Graph * , int , int );// O(Total No. of edges adjacent to the vertex)
void buildGraph( Graph * , int );// O(V)

void depth_first_search( Graph * , int , int );// O(V+E)
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
	depth_first_search( &head , a , n );
	for( int i = 0 ; i < n ; i++ )
	{
		printf(" Vertex %d Discovered at time %d." , i , head.arr[i].Time );
		printf("  The path is given below \n" );
		print_path( head , i , a );
		printf("\n");
	}	
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
		temp->arr[i].Time = -1;
		temp->arr[i].next = NULL;
	}
}

void depth_first_search( Graph *head , int start , int n )
{
	Stack *head1 = NULL;
	Edge *temp = NULL;
	int a = 0;
	int visited[n];
	int c = 0;
	for( int i = 0 ; i < n ; i++ )
		visited[i] = 0;
	visited[start] = 1;
	head->arr[start].Time = c++;
	push( &head1 , start );
	while( head1 != NULL )
	{
		a = pop( &head1 );
		temp = head->arr[a].next;
		while( temp != NULL )
		{
			if( visited[temp->vertex] == 0 )
			{
				push( &head1 , temp->vertex );
				visited[temp->vertex] = 1;
				head->arr[temp->vertex].Time = c;
				head->arr[temp->vertex].parent = a;
			}
			temp = temp->next;
		}
		c++;
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
		
		
		
		
	   

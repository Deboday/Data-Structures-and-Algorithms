/****************************************************************************************************************************************
*																	*
*						STRONGLY CONNECTED COMPONENTS								* *						   COMPLEXITY - O( V + E )						                * 
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

void depth_first_search( Graph * , int , Stack ** , int * );// O(V+E)
void print_path( Graph , int , int );

Stack * topological_sort( Graph * , int );

void transpose_graph( Graph * , Graph * , int );
void strongly_connected_components( Graph * , int );
void modified_dfs( Graph * , Stack ** , int );

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
	
	strongly_connected_components( &head , n );
	
	printf("\n The source vertex is 0 \n" );
	for( int i = 0 ; i < n ; i++ )
	{
		printf(" Vertex %d Discovered at time %d." , i , head.arr[i].Time );
		printf("  The path is given below \n" );
		print_path( head , i , 0 );
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

void depth_first_search( Graph *head , int start , Stack **out , int visited[] )
{
	Edge *temp = NULL;
	static int c = 0;
	
	visited[start] = 1;
	head->arr[start].Time = c++;
	
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

void transpose_graph( Graph *head , Graph *thead , int n )
{
	Edge *temp = NULL;
	for( int i = 0 ; i < n ; i++ )
	{
		temp = head->arr[i].next;
		while( temp != NULL )
		{
			addEdge( thead , temp->vertex , i );
			temp = temp->next;
		}
	}
}

void strongly_connected_components( Graph *head , int n )
{
	Graph thead;
	Stack *temp;
		
	buildGraph( &thead , n );
	
	temp = topological_sort( head , n );
	
	transpose_graph( head , &thead , n );
	
	printf("\n The Strongly Connected Components are \n" );
	modified_dfs( &thead , &temp , n );
}

void modified_dfs( Graph *head , Stack **temp , int n )
{
	int ver = 0;
	int visited[n];
	for( int i = 0 ; i < n ; i++ )
		visited[i] = 0;
	Stack *head2 = NULL;
	for( int i = 0 ; i < n ; i++ )
	{
		ver = pop( temp );
		if( visited[ver] == 0 )
		{
			depth_first_search( head , ver , &head2 , visited );
		}
		while( head2 != NULL )
		{			
			printf( "  %d  " , pop( &head2 ) );
			if( head2 == NULL )
			{
				printf("\n");
				break;
			}
		}			
	}
}
	
	
	
		
		
	 

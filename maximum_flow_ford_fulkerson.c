
/********************************************************************************************************************************
*																*
*							EDMONDS KARP ALGORITHM							*
*			FORD FULKERSON ALGORITHM WHERE THE PATH SEARCH IS DONE USING BREADTH FIRST SEARCH			*
*						TIME COMPLEXITY = O(E|F*|) = O(VE^2)						*
*					FOR ANALYSIS SEE PG. 729 OF INTRO TO ALGORITHMS( CORMEN )  				*
*																*
********************************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

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
		  	int capacity;
		  	int flow;
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

void enqueue( Queue ** , int );// O(1)
int dequeue( Queue ** );// O(1)

void addEdge( Graph * , int , int , int );// O(Total No. of edges adjacent to the given vertex)
void buildGraph( Graph * , int );// O(V)

void breadth_first_search( Graph * , Edge (*)[] , int , int , int );// O(V+E)

void augment_path( Graph * , Edge (*)[] , int , int , int );
void min_residual_capacity( Graph * , Edge (*)[] , int , int , int * );

int ford_fulkerson( Graph * , Edge (*)[] , int , int , int );



int main()
{
	Graph head;
	Edge residual_flow[N][N];
	int n = 0 , a = 0 , cap = 0;
	printf("Enter the total no. of vertices = " );
	scanf("%d" , &n );
	buildGraph( &head , n );
	printf("\n Enter the edges incident on the given vertex" );
	for( int i = 0 ; i < n ; i++ )
	{
		while( 1 )
		{
			printf("\n Enter the vertex adjacent to vertex %d. When done press -1 \n" , i ); 
			scanf("%d" , &a );
			if( a == -1 )
				break;
			printf("\nEnter the maximum capacity of this edge = " );
			scanf( "%d" , &cap );
			residual_flow[i][a].capacity = cap;
			addEdge( &head , i , a , cap );
		}
	}
	printf("\nEnter the source vertex = " );
	scanf("%d" , &a );
	printf("\nEnter the terminal vertex = " );
	scanf("%d" , &cap );
	printf("\nMaximum flow in the network = %d \n" , ford_fulkerson( &head , residual_flow , a , cap , n ) );
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

void addEdge( Graph *temp , int vertex1 , int vertex2 , int capacity )
{
	Edge *i = NULL;
	
	Edge *ab = ( Edge * )malloc( sizeof( Edge ) );
	ab->vertex = vertex2;
	ab->flow = 0;
	ab->capacity = capacity;
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

void breadth_first_search( Graph *head , Edge residual_flow[][N] , int start , int end , int n )
{
	Queue *head1 = NULL;
	Edge *temp = NULL;
	int a = 0 , c = 0;
	int visited[n];
	for( int i = 0 ; i < n ; i++ )
	{
		visited[i] = 0;
		head->arr[i].parent = -1;
	}
	visited[start] = 1;
	enqueue( &head1 , start );
	while( head1 != NULL )
	{
		a = dequeue( &head1 );
		temp = head->arr[a].next;
		while( temp != NULL )
		{
			if( visited[temp->vertex] == 0 && residual_flow[a][temp->vertex].flow < residual_flow[a][temp->vertex].capacity )
			{
				enqueue( &head1 , temp->vertex );
				visited[temp->vertex] = 1;
				head->arr[temp->vertex].parent = a;
				if( temp->vertex == end )
				{
					c = 1;
					break;
				}
			}
			temp = temp->next;
		}
		if( c == 1 )
			break;
	}
}

void min_residual_capacity( Graph *head , Edge residual_flow[][N] , int start , int end , int *min )
{
	if( start != end )
	{
		min_residual_capacity( head , residual_flow , start , head->arr[end].parent , min );
		if( *min > residual_flow[head->arr[end].parent][end].capacity - residual_flow[head->arr[end].parent][end].flow )
			*min = residual_flow[head->arr[end].parent][end].capacity - residual_flow[head->arr[end].parent][end].flow;
	}
}

int ford_fulkerson( Graph *head , Edge residual_flow[][N] , int source , int terminal , int n )//O(VE^2)
{
	int max_flow = 0;
	for( int i = 0 ; i < n ; i++ )//Setting the flow to 0
	{
		for( int j = 0 ; j < n ; j++ )
		{
			residual_flow[i][j].flow = 0;
		}
	}
	while(1)
	{
		breadth_first_search( head , residual_flow , source , terminal , n );//Finding the path
		if( head->arr[terminal].parent == -1 )//Terminating if there is no path
			break;
		int min_cap = INT_MAX; 
		min_residual_capacity( head , residual_flow , source , terminal , &min_cap );//Finding the minimum residual capacity of all the edges in the path
		max_flow = max_flow + min_cap;
		augment_path( head , residual_flow , source , terminal , min_cap );//Augmenting the residual flow and the Network flow
	}
	return max_flow;
}

void augment_path( Graph *head , Edge residual_flow[][N] , int start , int end , int min )
{
	if( start != end )
	{
		augment_path( head , residual_flow , start , head->arr[end].parent , min );
		residual_flow[head->arr[end].parent][end].flow = residual_flow[head->arr[end].parent][end].flow + min;
	}
}

	

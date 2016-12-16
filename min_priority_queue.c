#include<stdio.h>
#include<stdlib.h>

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
	    
	    		
	   	    

void min_heap_insert( QUEUE * , int , int );
int min_heap_extract( QUEUE * );
int min_heap_minimum( QUEUE );
void decrease_key( QUEUE * , int , int );
void min_heapify( QUEUE * , int , int );

void menu();	    
	    
int main()
{
	QUEUE head = { .length = -1 };
	int choice = 0 , el = 0 , key = 0;
	menu();
	while(1)
	{
		printf( " Enter your choice \n" );
		scanf( "%d" , &choice );
		switch( choice )
		{
		
			case 1 :
				printf( " Enter the no. and its key to insert in the MIN PRIORITY QUEUE \n" );
				scanf( "%d%d" , &el , &key );
				min_heap_insert( &head , el , key );
				break;
				
			case 2 :
				if( head.length == -1 )
				{
					printf( " The QUEUE is empty \n" );
				}
				else
				{
					printf( " %d \n" , min_heap_extract( &head ) );
				}
				break;
				
			case 3 :
				if( head.length == -1 )
				{
					printf( " The MIN PRIORITY QUEUE is empty \n" );
				}
				else
				{
					printf( " %d \n" , min_heap_minimum( head ) );
				}
				break;	
							
			case 4 :
				exit(0);
				
			default :
				printf( " Wrong Choice . Enter an appropriate choice \n" );
				break;
				
		}
	}
	return 0;			
}

void menu()
{

	printf( " The MIN PRIORITY QUEUE is initialized \n" );
	printf( " Enter 1 to ENQUEUE in the MIN PRIORITY QUEUE \n" );
	printf( " Enter 2 to DEQUEUE an element from the MIN PRIORITY QUEUE \n" );
	printf( " Enter 3 to PEEK in the MIN PRIORITY QUEUE \n" );
	printf( " Enter 4 to exit from the MIN PRIORITY QUEUE \n" );
	
}

void min_heap_insert( QUEUE *head , int el , int key )
{
	if( head->length == N )
		return;
	Object temp = { el , key };
	head->arr[++head->length] = temp;
	decrease_key( head , head->length , key );
}

int min_heap_extract( QUEUE *head )
{
	int el = head->arr[0].n;
	head->arr[0] = head->arr[head->length--];
	min_heapify( head , 0 , head->length );
	return el;
}

int min_heap_minimum( QUEUE head )
{
	return head.arr[0].n;
}

void decrease_key( QUEUE *head , int index , int key )
{
	if( head->arr[index].key < key )
		return;
	int i = index;
	while( i > 0 && head->arr[i/2].key > key )
	{
		Object temp = head->arr[i/2];
		head->arr[i/2] = head->arr[i];
		head->arr[i] = temp;
		i = i / 2;
	}
}

void min_heapify( QUEUE *head , int i , int n )
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
	
	if( i != min )
		min_heapify( head , min , n );
}


	

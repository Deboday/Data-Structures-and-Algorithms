#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

void menu();	    
	    
int main ()
{
	QUEUE *head = NULL , *tail = NULL;
	int choice = 0 , el = 0 ;
	menu();
	while(1)
	{
		printf( " Enter your choice \n" );
		scanf( "%d" , &choice );
		switch( choice )
		{
		
			case 1 :
				printf( " Enter the no. to insert in the QUEUE \n" );
				scanf( "%d" , &el );
				enqueue( &head , &tail , el );
				break;
				
			case 2 :
				if( is_empty( head ) == true )
				{
					printf( " The QUEUE is empty \n" );
				}
				else
				{
					printf( " %d \n" , dequeue( &head , &tail ) );
				}
				break;
				
			case 3 :
				if( is_empty( head ) == true )
				{
					printf( " The QUEUE is empty \n" );
				}
				else
				{
					printf( " %d \n" , peek( head ) );
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

	printf( " The QUEUE is initialized \n" );
	printf( " Enter 1 to ENQUEUE in the QUEUE \n" );
	printf( " Enter 2 to DEQUEUE an element from the QUEUE \n" );
	printf( " Enter 3 to PEEK in the QUEUE \n" );
	printf( " Enter 4 to exit from the QUEUE \n" );
	
}

void enqueue( QUEUE **head , QUEUE **tail , int element )
{
	QUEUE *temp = NULL;
	temp = ( QUEUE * )malloc( sizeof( QUEUE ) );
	temp->info = element;
	temp->next = NULL;
	if( temp == NULL )
	{
		printf( " MEMORY FULL \n" );
		return;
	}
	if( *head == NULL )
	{
		*head = *tail = temp;
		return;
	}
	( *tail )->next = temp;
	*tail = temp;
}

int dequeue( QUEUE **head , QUEUE **tail )
{
	QUEUE *temp = NULL;
	int re = 0;
	if( *head == NULL )
	{
		return;
	}
	temp = *head;
	*head = ( *head )->next;
	if( *head == NULL )
	{
		*tail = NULL;
	}
	re = temp->info;
	free( temp );
	return re;
}

boolean is_empty( QUEUE *head )
{
	if( head == NULL )
	{
		return true;
	}
	return false;
}

int peek( QUEUE *head )
{
	if( head == NULL )
	{
		return; 
	}
	return head->info;	
}

void empty( QUEUE **head , QUEUE **tail )
{
	QUEUE *i = *head , *hold = NULL; 
	while( i != NULL )
	{
		hold = i;
		i = i->next;
		free( hold );
	}
	*tail = NULL;
}
	
		

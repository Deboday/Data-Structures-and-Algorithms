#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

void menu();	    
	    
int main ()
{
	STACK *head = NULL;
	int choice = 0 , el = 0 ;
	menu();
	while(1)
	{
		printf( " Enter your choice \n" );
		scanf( "%d" , &choice );
		switch( choice )
		{
		
			case 1 :
				printf( " Enter the no. to insert in the STACK \n" );
				scanf( "%d" , &el );
				push( &head , el );
				break;
				
			case 2 :
				if( is_empty( head ) == true )
				{
					printf( " The STACK is empty \n" );
				}
				else
				{
					printf( " %d \n" , pop( &head ) );
				}
				break;
				
			case 3 :
				if( is_empty( head ) == true )
				{
					printf( " The STACK is empty \n" );
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

	printf( " The STACK is initialized \n" );
	printf( " Enter 1 to PUSH in the STACK \n" );
	printf( " Enter 2 to POP an element from the STACK \n" );
	printf( " Enter 3 to PEEK in the STACK \n" );
	printf( " Enter 4 to exit from the STACK\n" );
	
}  

void push( STACK **head , int element )
{
	STACK *temp = NULL;
	temp = ( STACK * )malloc( sizeof( STACK ) );
	temp->info = element;
	temp->next = *head;
	if( temp == NULL )
	{
		printf( " MEMORY FULL \n" );
		return;
	}
	if( *head == NULL )
	{
		*head = temp;
		return;
	}
	*head = temp;
}

int pop( STACK **head )
{
	STACK *temp = NULL;
	int re = 0;
	if( *head == NULL )
	{
		return;
	}
	temp = *head;
	*head = ( *head )->next;
	re = temp->info;
	free( temp );
	return re;
}

boolean is_empty( STACK *head )
{
	if( head == NULL )
	{
		return true;
	}
	return false;
}

int peek( STACK *head )
{
	if( head == NULL )
	{
		return; 
	}
	return head->info;	
}

void empty( STACK **head )
{
	STACK *i = *head , *hold = NULL; 
	while( i != NULL )
	{
		hold = i;
		i = i->next;
		free( hold );
	}
}
	

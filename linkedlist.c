#include<stdio.h>
#include<stdlib.h>
#include"linkedlist.h"		
		
/*int main ()
{
	node *head;
	head = NULL;
	int choice = 0 , el = 0 ;
	menu();
	while(1)
	{
		printf( " Enter your choice \n" );
		scanf( "%d" , &choice );
		switch( choice )
		{
		
			case 1 :
				printf( " Enter the no. to insert in the Linked List \n" );
				scanf( "%d" , &el );
				insert_end( &head , el );
				break;
				
			case 2 :
				delete_end( &head );
				break;
				
			case 3 :
				printf( " Enter the no. to insert at the beginning of the Linked List \n" );
				scanf( "%d" , &el );
				insert_begin( &head , el );
				break;
				
			case 4 :
				delete_begin( &head );
				break;
				
			case 5 :
				printf( " Enter the no. to delete from the Linked List \n" );
				scanf( "%d" , &el );
				delete( &head , el );
				break;
				
			case 6 :
				printf( " Enter the no. to insert in the Linked List in sorted order \n" );
				scanf( "%d" , &el );
				sort_entry( &head , el );
				break;
				
			case 7 :
				merge_sort( &head );
				display( head ) ;
				break;
				
			case 8 :
				display( head );
				break;
				
			case 9 :				
				if( is_empty( &head ) == true )
				{
					printf( " Empty List \n" );
				}
				else
				{
					recursive_reversing( &head );
					display( head );
				}
				break;
				
			case 10 :
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

	printf( " The Linked List is initialized \n" );
	printf( " Enter 1 to insert an element at the end in the Linked List \n" );
	printf( " Enter 2 to delete the last element from the Linked List \n" );
	printf( " Enter 3 to insert at the beginning of the Linked List \n" );
	printf( " Enter 4 to delete from the beginning of the Linked List \n" ); 
	printf( " Enter 5 to delete an element from the Linked List \n" );
	printf( " Enter 6 to insert an element in sorted order \n" );
	printf( " Enter 7 to sort the Linked list \n" );
	printf( " Enter 8 to display the Linked List \n" );
	printf( " Enter 9 to reverse the Linked List \n" );
	printf( " Enter 10 to exit from the Linked List \n" );
	
}*/

void insert_end( node **head , int info )
{
	
	node *temp = NULL , *i = NULL;
	temp = ( node * )malloc( sizeof( node ) );
	if( temp == NULL )
	{
		printf( " Memory Full . Empty some elements and try again \n" );
		return;
	}
	temp->element = info;
	temp->next = NULL;
	if( *head == NULL )
	{
		*head = temp;
		return;
	}
	for( i = *head ; i->next != NULL ; i = i->next );
	i->next = temp;
	
}

void delete_end( node **head )
{
	
	node *i = NULL , *previous = NULL;
	if( *head == NULL )
	{
		printf( " List is Empty \n" );
		return;
	}
	if( ( *head )->next == NULL )
	{
		previous = *head;
		*head = NULL;
		free( i );
	}
	for( i = *head ; i->next != NULL ; previous = i , i = i->next );	
	previous->next = NULL;
	free( i );
	
}

void display( node *head )
{
	node *i;
	if( head == NULL )
	{
		printf(" The List is empty \n" );
		return;
	}
	printf( " Displaying the Linked List \n" );
	for( i = head ; i != NULL ; i = i->next )
	{
		if( i->next != NULL )
		{
			printf( "%d -> " , i->element );
		}
		else
		{
			printf( "%d \n" , i->element );
		}
	}
}

void insert_begin( node **head , int info )
{

	node *temp = NULL;
	temp = ( node * )malloc( sizeof( node ) );
	if( temp == NULL )
	{
		printf( " Memory Full . Empty some elements and try again \n" );
		return;
	}
	temp->element = info;
	temp->next = *head;
	if( *head == NULL )
	{
		*head = temp;
		return;
	}
	*head = temp;
		
}

void delete_begin( node **head )
{
	node *temp = NULL ;
	if( *head == NULL )
	{
		printf( " List is Empty already \n" );
		return;
	}
	if( *head != NULL && ( *head )->next == NULL )
	{		
		free ( *head );
		*head = NULL;
		return;
	}
	temp = *head;
	*head = (*head)->next;
	free(temp);
	
}

void delete( node **head , int info )
{

	node *previous = NULL , *current = NULL , *i = NULL ;
	if( *head == NULL )
	{
		printf( " List is Empty \n" );
		return;
	}
	if( (*head)->element == info )
	{
		i = *head;
		*head = (*head)->next;
		free( i );
		return;
	}
	previous = *head;		
	for( i = *head ; i != NULL && i->element != info ; previous = i , i = i->next , current = i );
	if( i != NULL )
	{
		previous->next = current->next;
		free( current );
	}
	else
	{ 
		printf( " Element not in Linked List \n" );
	}
	
}

boolean is_empty ( node **head )
{
	if( *head == NULL )
	{
		return true;
	}
	return false;
}


void sort_entry( node **head , int info )
{
	node *temp = NULL , *i = NULL , *previous = NULL , *current = NULL;
	temp = ( node * )malloc( sizeof( node ) );
	if( temp == NULL )
	{
		printf( " Memory Full \n" );
		return;
	}
	temp->element = info;
	temp->next = NULL;
	if( *head == NULL )
	{
		*head = temp;
		return;
	}
	if( (*head)->element > info )
	{
		temp->next = *head;
		*head = temp;
		return;		
	}
	previous = *head;
	for( i = *head ; i != NULL && i->element <= info ; previous = i , i = i->next , current = i );
	if( i != NULL )
	{
		temp->next = current;
		previous->next = temp;
	}
	else
	{
		previous->next = temp;
	}
}

int length( node **head )
{
	 node *i = NULL;
	 int n = 0;
	 for( i = *head ; i != NULL ; n++ , i = i->next );
	 return n;
}

void new_node( node **temp )
{
	*temp = ( node * )malloc( sizeof( node ) );
	if( *temp == NULL )
	{
		printf( " No Memory \n" );
		return;
	}
}

void merge_sort( node **head )
{
	node *left = NULL , *right = NULL , *temp = NULL;
	if( *head == NULL || ( *head )->next == NULL )
	{
		return;
	}
	left = *head;
	mid_split( &left , &right , *head ); 
	merge_sort( &left );
	merge_sort( &right );
	*head = NULL;
	sorted_merge( head , left , right );
}

void mid_split( node **left , node **right , node *head )
{	 
	if( head->next == NULL )
	{
		*right = ( *left )->next;
		( *left )->next = NULL;
	}
	else if( head->next->next == NULL )
	{
		*right = ( *left )->next;
		( *left )->next = NULL;
	}
	else
	{		
		mid_split( &( ( *left )->next ) , right , head->next->next );
	}
}

void sorted_merge( node **head , node *left , node *right )
{
	if( left == NULL )
	{
		if( *head == NULL )
		{
			*head = right;
		}
		else
		{
			( *head )->next = right;
		}
	}
	else if( right == NULL )
	{
		if( *head == NULL )
		{
			*head = left;
		}
		else
		{
			( *head )->next = left;
		}
	}
	else
	{
		if( left->element <= right->element )
		{
			if( *head == NULL )
			{
				*head = left;
				sorted_merge( head , left->next , right );
			}
			else
			{
				( *head )->next = left;
				sorted_merge( &( ( *head )->next ) , left->next , right );
			}
		}
		else
		{ 
			if( *head == NULL )
			{
				*head = right;
				sorted_merge( head , left , right->next );
			}
			else
			{
				( *head )->next = right;
				sorted_merge( &( ( *head )->next ) , left , right->next );
			}
		}
	}
}

void recursive_reversing( node **head )
{
	node *temp = NULL;
	if( ( *head )->next == NULL )
	{
		return;
	}
	temp = ( *head )->next;
	recursive_reversing( &temp );
	temp->next = *head;
	temp = ( *head )->next;
	( *head )->next = NULL;
	*head = temp;
		
}
			
	
		

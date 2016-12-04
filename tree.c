#include<stdio.h>
#include<stdlib.h>
#include"stack.c"


#define true 1
#define false 0

#define MAX( x , y ) \
			 x > y ? x : y

typedef int boolean;

typedef struct link {
		int info;
		struct link *left;
		struct link *right;
		int height;
	    } node;
	    
	    
void new_node( node ** );
void insert( node ** , int );
void menu();
void preorder( node * );
void inorder( node * );
void postorder( node * );
int count( node * );
int height1( node * );
void has_path_sum( node * , int , boolean * );
void print_paths( node * );
void print_stack( STACK * );
node * delete_node( node ** , int );
void del_special( node ** );
//void tree_to_list( node ** , node ** );
//void join( node ** , node ** );
void display_link( node * );
void avl_insert( node ** , int );
void right_rotation( node ** );
void left_rotation( node ** );
void update_height( node ** );
	    
int main()
{
	node *head = NULL , *list = NULL;
	int choice = 0 , element = 0 , el = 0;
	boolean con = false , *p = &con;
	menu();
	while(1)
	{
		printf( " Enter your choice \n" );
		scanf( "%d" , &choice );
		switch( choice )
		{
		
			case 1 :
				printf( " Enter the no. to insert in the Binary Search Tree \n" );
				scanf( "%d" , &el );
				insert( &head , el );
				break;
				
			case 2 :
				printf( " Displaying the Binary Search Tree in preorder form \n" );
				preorder( head );
				printf( "\n" );
				break;
				
			case 3 :
				printf( " Displaying the Binary Search Tree in inorder form \n" );
				inorder( head );
				printf( "\n" );
				break;
				
			case 4 :
				printf( " Displaying the Binary Search Tree in postorder form \n" );
				postorder( head );
				printf( "\n" );
				break;
				
			/* Height of a tree is the number of edges along the longest path */
				
			case 5 :
				printf( " The height of the Binary Search Tree is %d \n" , height1( head ) );
				break;
				
			case 6 :
				printf( " The number of nodes in the Binary Search Tree is %d \n" , count( head ) );
				break;
				
			/* Depth of a tree is the number of nodes along the longest path */
				
			case 7 :
				printf( " The depth of the Binary Search Tree is %d \n" , height1( head ) + 1 );
				break;
				
			case 8 :
				printf( " Enter the path sum you want to check whether it is present or not \n" );
				scanf( "%d" , &el );
				*p = false;
				has_path_sum( head , el , p );
				if( *p == false )
				{
					printf( " No such path sum present in the Binary Search Tree \n" );
				}
				else
				{
					printf( " Path Sum is present in the Binary Search Tree \n" );
				}
				break;
				
			case 9 : 
				if( head == NULL )
				{
					printf( " Empty Tree \n" );
				}
				else
				{
					printf( " Displaying all possible paths \n" );
					print_paths( head );
				}				 
				break;
				
			case 10 :
				if( head == NULL )
				{
					printf( " Empty Tree \n" );
				}
				else
				{
					printf( " Enter the no. to delete from the Binary Search Tree \n" );
					scanf( "%d" , &el );
					head = delete_node( &head , el );
				}
				break;		
				
			case 11 :
				printf( " Enter the no. to insert in the AVL Tree \n" );
				scanf( "%d" , &el );
				avl_insert( &head , el );
				break;
				
			case 12 :
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
	printf( " The Binary Search Tree is initialized \n" );
	printf( " Enter 1 to insert an element in the Binary Search Tree \n" );
	printf( " Enter 2 to display the Binary Search Tree in Preorder Form \n" );
	printf( " Enter 3 to display the Binary Search Tree in Inorder Form \n" );
	printf( " Enter 4 to display the Binary Search Tree in Postorder Form \n" );
	printf( " Enter 5 to display the height of the Binary Search Tree \n" );
	printf( " Enter 6 to count the number of nodes in the Binary Search Tree \n" );
	printf( " Enter 7 to find the depth of the Binary Search Tree \n" );
	printf( " Enter 8 to find whether Path Sum is present or not \n" );
	printf( " Enter 9 to find all the possible paths \n" );
	printf( " Enter 10 to delete an element from the Binary Search Tree \n" );
	printf( " Enter 11 to insert an element in the AVL Tree \n" );
	printf( " Enter 12 to close the Binary Search Tree \n" );	
}		
		
void new_node ( node **temp )
{
	*temp = ( node * )malloc( sizeof( node ) );
}

void insert ( node **head , int data )
{
	node *temp = NULL , *i = NULL;
	new_node( &temp );	    
	if( temp == NULL )
	{
		printf( " MEMORY FULL \n" );
		return;
	}
	temp->info = data;
	temp->left = temp->right = NULL;	
	if( *head == NULL )
	{
		*head = temp;
		return;
	}
	i = *head;
	while( i != NULL )
	{
		if( data <= i->info )
		{
			if( i->left == NULL )
			{
				i->left = temp;
				return;
			}
			else
			{
				i = i->left;
			}
		}				
		else
		{
			if( i->right == NULL )
			{
				i->right = temp;
				return;
			}
			else
			{
				i = i->right;
			}
		}
	}
}

void preorder ( node *head )
{
	if( head != NULL )
	{
		printf( " %d " , head->info );
		preorder( head->left );
		preorder( head->right );
	}
}

void inorder ( node *head )
{
	if( head != NULL )
	{
		inorder( head->left );
		printf( "  %d  " , head->info );
		inorder( head->right );
	}
}

void postorder ( node *head )
{
	if( head != NULL )
	{		
		postorder( head->left );
		postorder( head->right );
		printf( "  %d  " , head->info );
	}
}

int height1( node *tree ) // HEIGHT = NO. OF EDGES // DEPTH = NO OF NODES
{
	int left = 0 , right = 0;
	if( tree == NULL )
	{
		return -1;
	}
	left = height1( tree->left );
	right = height1( tree->right );
	return ( MAX( left , right ) + 1 );
}

int count( node *head )
{
	static c = 0;
	if( head != NULL )
	{
		c++;
		count( head->left );
		count( head->right );
	}
	return c;
}

int min_value( node *head )
{
	if( head->left == NULL )
	{
		return head->info;
	}
	min_value( head->left );
}

void has_path_sum( node *head , int data , boolean *p )
{
	static sum = 0;
	if( head->left == NULL && head->right == NULL )
	{
		if( data == ( sum + head->info ) )
		{
			*p = true;
			return;
		}				
	}
	sum = sum + head->info;
	if( head->left != NULL )
	{
		has_path_sum( head->left , data , p );
		sum = sum - head->info;
	}
	if( head->right != NULL )
	{
		has_path_sum( head->right , data , p );
		sum = sum - head->info;
	}
}

void print_stack( STACK *head )
{
	if( head == NULL )
	{
		return;
	}
	while( head->next != NULL )
	{
		printf( "%d <- " , head->info );
		head = head->next;
	}
	printf( "%d" , head->info );
	printf( "\n" );
}

void print_paths( node *head )
{
	static STACK *temp = NULL;
	if( head->left == NULL && head->right == NULL )
	{
		push( &temp , head->info );
		print_stack( temp );
		pop( &temp );
		return;
	}
	push( &temp , head->info );
	if( head->left != NULL )
	{
		print_paths( head->left );		
	}
	if( head->right != NULL )
	{
		print_paths( head->right );
	}
	pop( &temp );
}

node * delete_node( node **head , int data )
{
	node *temp = *head , *hold = *head;
	if( *head == NULL )
	{
		printf( " No Such Data in Tree \n" );
		return;
	}
	if( ( *head )->info == data )
	{
		if( temp->left == NULL && temp->right == NULL )
		{
			free( temp );
			hold = NULL;
		}
		else if( temp->left == NULL && temp->right != NULL )
		{
			hold = temp->right;
			free( temp );
		}
		else if( temp->left != NULL && temp->right == NULL )
		{
			hold = temp->left;
			free( temp );
		}
		else if( temp->left != NULL && temp->right != NULL )
		{
			del_special( head );
		}		
	}
	else if( data < temp->info )
	{
		temp->left = delete_node( &( temp->left ) , data );
	}
	else
	{
		temp->right = delete_node( &( temp->right ) , data );
	}
	return hold;
}

void del_special( node **head )
{
	node *temp = *head , *hold = temp->right->left , *i = NULL;
	if( hold == NULL )
	{
		temp->info = temp->right->info;
		hold = temp->right;
		temp->right = temp->right->right;
		free( hold );
		return;
	}
	else
	{
		if( hold->left == NULL )
		{
			temp->info = hold->info;
			if( hold->right != NULL )
			{
				temp->right->left = hold->right;
			}
			else
			{
				temp->right->left = NULL;
			}
			free( hold );
			return;
		}
		while( hold->left->left != NULL )
		{
			hold = hold->left;
		}
		temp->info = hold->left->info;
		i = hold->left;
		if( hold->left->right != NULL )
		{
			hold->left = hold->left->right;
		}
		else
		{
			hold->left = NULL;
		}
		free( i );
	}
}

boolean leaf( node *head )
{
	if( head->left == NULL && head->right == NULL )
	{
		return true;
	}
	return false;
}
// AVL TREE

void avl_insert( node **head , int element )
{
	node *temp = NULL , *i = *head;
	int left = -1 , right = -1 , diff = 0;
	if( *head == NULL )
	{
		new_node( &temp );
		temp->info = element;
		temp->left = NULL;
		temp->right = NULL;
		temp->height = 0;
		*head = temp;				
		return;
	}	
	if( element < i->info )
	{
		if( i->left != NULL )
		{
			avl_insert( &( i->left ) , element );
		}
		else
		{
			new_node( &temp );
			temp->info = element;
			temp->left = NULL;
			temp->right = NULL;
			temp->height = 0;
			i->left = temp;	
		}
	}
	else
	{
		if( i->right != NULL )
		{
			avl_insert( &( i->right ) , element );
		}
		else
		{
			new_node( &temp );
			temp->info = element;
			temp->left = NULL;
			temp->right = NULL;
			temp->height = 0;
			i->right = temp;	
		}
	}
	if( i->left != NULL )
	{
		left = i->left->height;
	} 
	if( i->right != NULL )
	{
		right = i->right->height;
	} 
	i->height = MAX( left , right ) + 1;
	diff = left - right;
	if( diff > 1 )
	{
		if( i->left->left != NULL )
		{
			right_rotation( head );
		}
		else
		{
			left_rotation( &( i->left ) );
			right_rotation( head );
		}
	}
	else if( diff < -1 )
	{
		if( i->right->right != NULL )
		{
			left_rotation( head );
		}
		else
		{
			right_rotation( &( i->right ) );
			left_rotation( head );
		}
	}
}

void update_height( node **head )
{
	node *i = *head;
	int left = -1 , right = -1;
	if( i->left != NULL )
	{
		left = i->left->height;
	}
	if( i->right != NULL )
	{
		right = i->right->height;
	}
	i->height = MAX( left , right ) + 1;
}

// ROTATIONS

void left_rotation( node **head )
{
	node *temp = *head , *i = temp->right;
	*head = i;
	temp->right = i->left;
	i->left = temp;
	update_height( &temp );
	update_height( head );
}
	
void right_rotation( node **head )
{
	node *temp = *head , *i = temp->left;
	*head = i;
	temp->left = i->right;
	i->right = temp;	
	update_height( &temp );
	update_height( head );	
}
	
			
		
			
	
	
		


	
	 






	

			
		

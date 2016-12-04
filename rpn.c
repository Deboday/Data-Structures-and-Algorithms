#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

#define N 100

typedef struct s
		{
			int arr[N];
			int top;
		
		} STACK;
		
		

void menu();
void push( STACK * , int );
int pop( STACK * );
int peek( STACK );

int val( char a );
void postfix( char * );
void post_eval( char * );

int main()
{
	int choice = 0 ;
	char arr[100];
	menu();
	while(1)
	{
		printf( " Enter your choice \n" );
		scanf( "%d" , &choice );
		switch( choice )
		{
		
			case 1 :
				printf( " Enter the Infix Expression \n" );
				scanf("%s",&arr);
				postfix(arr);
				//prefix(arr);
				break;
				
			/*case 2 :
				
				printf( " Enter the Prefix Expression \n" );
				gets(arr);
				infix(arr);
				pre_post(arr);
				break;
				
			case 3 :
				
				printf( " Enter the Postfix Expression \n" );
				gets(arr);
				infix(arr);
				post_pre(arr);
				break;*/	
							
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

	printf( " The Program is initialized \n" );
	printf( " Enter 1 to enter Infix Expression \n" );
	printf( " Enter 2 to enter Prefix Expression \n" );
	printf( " Enter 3 to enter Postfix Expression \n" );
	printf( " Enter 4 to exit \n" );
	
}


int val( char a )
{
	switch( a )
	{
		case '+' :
				return 1;
		case '-' : 
				return 1;
		case '*' :
				return 3;
		case '^' :	
				return 4;
	}
}

int con( int a )
{
	if( a >=48 && a <= 57 )
		return a - 48;
	return a;
}



void postfix( char arr[] )
{
	int len = strlen(arr) , i = 0  , c = 0;
	char eval[len];
	STACK head = { .top = 0 };
	for( i = 0 ; i < len ; i++ )
	{
		if( arr[i] == ')' )
		{
			while( (char)peek( head ) != '(' )
				eval[c++] = (char)pop( &head );
			pop( &head );
			continue;
		}
		if( arr[i] == '(' )
		{
			push( &head , (int)arr[i] );
			continue;
		}		
		if( !(isdigit(arr[i])) )
		{
			while( head.top > 0 && head.arr[head.top-1] != '(' && val( (char)peek( head ) ) > val( (char)arr[i] ) )
			{
				eval[c++] = (char)pop( &head );
			}
			push( &head , (int)arr[i] );
		}
		else
			eval[c++] = arr[i];
		/*printf("\n");
		puts(eval);
		printf("\n");*/
	}
	while( head.top != 0)
	{
		eval[c++] = (char)pop( &head );
	}
	eval[c] = '\0';
	printf( "\nThe Postfix Expression  is \n" );
	puts(eval);
	post_eval( eval );
}


void post_eval( char arr[] )
{
	int len = strlen(arr) , i = 0  , val = 0 , temp1 = 0 , temp2 = 0;
	STACK head = { .top = 0 };
	for( i = 0 ; i < len ; i++ )
	{
		if( !(isdigit(arr[i])) )
		{
			temp1 = con( pop( &head ) );
			temp2 = con( pop( &head ) );
			switch(arr[i])
			{
				case '+' :						
						push( &head , temp2 + temp1 );
						break;
						
				case '-' :
						push( &head , temp2 - temp1 );
						break;
						
				case '*' :
						push( &head , temp2 * temp1 );
						break;
						
				case '^' :
						push( &head , (int)pow( temp2 , temp1 ) );
						break;
			}
		}
		else
			push( &head , (int)arr[i] );
	}
	printf( "\nThe output is %d \n" , pop( &head ) );
}
					
	
	




/************************************************************************************************************************
*														       	*
*														       	*		
*						THE STACK FUNCTIONS							*
*															*
*															*
*************************************************************************************************************************/

void push( STACK *head , int a )
{
	if( head->top != N )
	{
		head->arr[(head->top)++] = a;
		//printf( " Stack push %c %d\n " ,  head->arr[(head->top)-1] , head->top);
	}
	else 
	{
		//printf( " Stack Full \n " );
		exit(0);
	}
} 

int pop( STACK *head )
{
	if( head->top == 0 )
	{
		//printf( " Stack Empty \n " );
		exit(0);
	}
	else
	{
		//printf( " Stack pop %c %d\n " ,  head->arr[(head->top)-1] , head->top);
		return head->arr[--(head->top)];
	}
}

int peek( STACK head )
{
	if( head.top == 0 )
	{
		//printf( " Stack Empty \n " );
		exit(0);
	}
	else
	{
		//printf( " Stack peek %c %d\n " ,  head.arr[(head.top)-1] , head.top);
		return head.arr[head.top - 1];
	}
}		

#include<stdio.h>
#include<string.h>

#define N 50

void optimal_solution( char * , char * , int (*)[] , int (*)[] );
void optimal_solution_print( char * , int (*)[] , int , int );

int main()
{
	int lcs[N][N] , pre[N][N];
	int n = 0 , i = 0 , j = 0;
	char arr1[N] , arr2[2];
	
	printf("Enter the 1st String = ");
	gets(arr1);
	printf("\nEnter the 2nd String = ");
	gets(arr2);
	
	optimal_solution( arr1 , arr2 , lcs , pre );
	printf("\nThe length of the longest common subsequence of length %d is " , lcs[strlen(arr1)][strlen(arr2)] );
	optimal_solution_print( arr1 , pre , strlen( arr1 ) , strlen( arr2 ) );
	
	printf("\n");
	printf("\nThe LCS Matrix is \n " );
	for( i = 1 ; i <= strlen(arr1) ; i++ )
		printf( "  %d  " , i );
	printf("\n");
	for( i = 1 ; i <= strlen(arr1) ; i++ )
	{
		printf("%d" , i );
		for( j = 1 ; j <= strlen(arr2) ; j++ )
		{
			printf( "  %d  " , lcs[i][j] );
		}
		printf("\n");
	}
	
	printf("\nThe Prefix Matrix is \n " );
	printf("1 for going diagonally up\n");
	printf("2 for going left\n");
	printf("3 for going up\n");
	for( i = 1 ; i <= strlen(arr1) ; i++ )
		printf( "  %d  " , i );
	printf("\n");
	for( i = 1 ; i <= strlen(arr1) ; i++ )
	{
		printf("%d" , i );
		for( j = 1 ; j <= strlen(arr2) ; j++ )
		{
			printf( "  %d  " , pre[i][j] );
		}
		printf("\n");
	}
	return 0;
}

void optimal_solution( char arr1[] , char arr2[] , int lcs[][N] , int pre[][N] )
{
	int m = strlen(arr1);
	int n = strlen(arr2);
	int i , j;
	for( int i = 0 ; i <= m ; i++ )
	{
		lcs[0][i] = 0;
	}
	for( int i = 0 ; i <= n ; i++ )
	{
		lcs[i][0] = 0;
	}
	for( int i = 1 ; i <= m ; i++ )
	{
		for( int j = 1 ; j <= n ; j++ )
		{
			if( arr1[i-1] == arr2[j-1] )
			{
				lcs[i][j] = lcs[i-1][j-1] + 1;
				pre[i][j] = 1;
			}
			else if( lcs[i-1][j] > lcs[i][j-1] )
			{
				lcs[i][j] = lcs[i-1][j];
				pre[i][j] = 2;
			}
			else
			{
				lcs[i][j] = lcs[i][j-1];
				pre[i][j] = 3;
			}
		}
	}
}

void optimal_solution_print( char arr[] , int pre[][N] , int i , int j )
{
	if( i == 0 || j == 0 )
		return;
	if( pre[i][j] == 1 )
	{
		optimal_solution_print( arr , pre , i - 1 , j - 1 );
		printf("%c" , arr[i-1] );
	}
	else if( pre[i][j] == 2 )
		optimal_solution_print( arr , pre , i - 1 , j );
	else
		optimal_solution_print( arr , pre , i , j - 1 );
}

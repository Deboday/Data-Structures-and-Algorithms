#include<stdio.h>
#include<stdlib.h>

#define N 50

#define INTEGER_MAX  256

void optimal_solution( int * , int * , int * , int );

int main()
{
	int i = 0 , len = 0;
	int price[N] , profit[N] , cut[N];
	printf("Enter the length of the Rod = ");
	scanf("%d" , &len );
	printf("Enter the prices \n");
	for( i = 1 ; i <= len ; i++ )
	{ 
		printf("\n Enter the price of a rod of length %d = " , i );
		scanf("%d" , &price[i] );
		profit[i] = INTEGER_MAX;
		cut[N] = i;
	}
	profit[0] = price[0] = cut[0] = 0;
	
	printf( "Max Profit By cutting the rods when the length is \n" );
	optimal_solution( price , profit , cut , len );

	printf( "The maximum profit and the first cut for the rod is \n" );
	while( len > 0 )
	{
		printf( " Length = %d  ,  Maximum Profit = %d  ,  First Cut = %d  \n" , len , profit[len] , cut[len] );
		len--;
	}
	return 0;
}

void optimal_solution( int price[] , int profit[] , int cut[] , int n )
{
	int max = 0;
	for( int i = 1 ; i <= n ; i++ )
	{
		max = 0;
		for( int j = 1 ; j <= i ; j++ )
		{
			if( max < price[j] + profit[i-j] )
			{
				cut[i] = j;
				max = price[j] + profit[i-j];
			}
		}
		profit[i] = max;
	}
}
		
			
	 
	
	

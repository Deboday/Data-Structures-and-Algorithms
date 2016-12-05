#include<stdio.h>
#include<stdlib.h>

#define N 50

#define INTEGER_MAX  256

int optimal_solution( int * , int * , int * , int );

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

int optimal_solution( int price[] , int profit[] , int cut[] , int i )
{
	int max = 0 , c = 0; 
	if( profit[i] != INTEGER_MAX )
		return profit[i];
	for( int j = 1 ; j <= i ; j++ )
	{
		c = price[j] + optimal_solution( price , profit , cut , i - j );
		if( max < c )
		{
			cut[i] = j;
			max = c;
		}
	}
	profit[i] = max;
	return profit[i];
}
		
			
	 
	
	

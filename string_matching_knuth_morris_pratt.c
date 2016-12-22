/********************************************************************************************************************************
*																*
*					KNUTH MORRIS PRAT STRING MATCHING ALGORITHM						*
*				        	TIME COMPLEXITY = O(M+E)							*
*				       PREPROCESSING TIME = O(M) , MATCHING TIME = O(N)						*
*				    FOR ANALYSIS SEE PG. 10002 OF INTRO TO ALGORITHMS( CORMEN )  				*
*				ALSO SEE THIS 2 VIDEOS I) https://www.youtube.com/watch?v=GTJr8OvyEVQ 				*
*						       II) https://www.youtube.com/watch?v=KG44VoDtsAA&t=237s 			*
*																*
********************************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 100

void kmp( char * , char * );
void compute_prefix_array( char * , int * );

int main()
{
	char text[N] , pattern[N];
	printf( "Enter the text where the pattern is to be searched = " );
	gets(text);
	printf( "\nEnter the pattern to be searched = " );
	gets(pattern);
	kmp( pattern , text );
	printf("\n");
	return -1;
}

void kmp( char pattern[] , char text[] )//O(M+N)
{
	int m = strlen(pattern);
	int n = strlen(text);
	int prefix[N];
	compute_prefix_array( pattern , prefix );
	int j = 0 , i = 0 , count = 0;
	while( i < n )
	{
		if( text[i] == pattern[j] )
		{
			i++;
			j++;
		}
		else
		{
			if( j > 0 )
				j = prefix[j-1];
			else
				i++;
		}
		if( j == m )
		{
			j = prefix[j-1];
			printf( "\nPattern occurs at position %d " , i - m );
			count++;
		}
	}
	if( count == 0 )
		printf("\nNo Such pattern in the text" );
}

void compute_prefix_array( char pattern[] , int prefix[] )//O(M)
{
	int m = strlen(pattern);
	prefix[0] = 0;
	int i = 1 , j = 0;
	while( i < m )
	{
		if( pattern[i] == pattern[j] )
		{
			prefix[i++] = ++j;
			continue;
		}
		if( pattern[i] != pattern[j] && j == 0 )
		{
			prefix[i++] = 0;
		}
		else
		{
			j = prefix[j-1];
		}
	}
}
		



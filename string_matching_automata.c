/********************************************************************************************************************************
*																*
*						   STRING MATCHING AUTOMATA							*
*				        TIME COMPLEXITY = O(M^3E) ; BEST POSSIBLE = O(ME)					*
*				    FOR ANALYSIS SEE PG. 996 OF INTRO TO ALGORITHMS( CORMEN )  					*
*																*
********************************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 100

void finite_automata( char * , char * );
int find_alphabets( char * , char * );
int find_index( char * , char , int );
void transition_function( char * , int (*)[] , char * , int );
int compare( char * , int , int );

int main()
{
	char text[N] , pattern[N];
	printf( "Enter the text where the pattern is to be searched = " );
	gets(text);
	printf( "\nEnter the pattern to be searched = " );
	gets(pattern);
	finite_automata( pattern , text );
	printf("\n");
	return -1;
}

void finite_automata( char pattern[] , char text[] )//O(M^3E)
{
	int m = strlen(pattern);
	int n = strlen(text);
	int state = 0 , count = 0;
	char alphabets[N];
	int c = find_alphabets( pattern , alphabets );
	int transition_table[m+1][N];
	transition_function( pattern , transition_table , alphabets , c );//O(M^3E)
	for( int i = 0 ; i < n ; i++ )
	{
		int index = find_index( alphabets , text[i] , c );
		if( index == -1 )
			state = 0;
		else
			state = transition_table[state][index];
		if( state == m )
		{
			printf( "\nPattern occurs at position %d " , i - m + 1 );
			count++;
		}
	}
	if( count == 0 )
		printf("\nNo Such pattern in the text" );
}

int find_alphabets( char pattern[] , char alphabets[] )
{
	int m = strlen(pattern);
	int c = 0;
	alphabets[c++] = pattern[0];
	for( int i = 1 ; i < m ; i++ )
	{
		int index = find_index( alphabets , pattern[i] , c );
		if( index == -1 )
			alphabets[c++] = pattern[i];
	}
	return c;
}

int find_index( char alphabets[] , char a , int c )
{
	for( int i = 0 ; i < c ; i++ )
		if( alphabets[i] == a )
			return i;
	return -1;
}

void transition_function( char pattern[] , int transition_table[][N] , char alphabets[] , int c )//O(M^3E)
{
	int m = strlen(pattern);//O(M)
	for( int state = 0 ; state <= m ; state++ )//O(M)
	{
		for( int j = 0 ; j < c ; j++ )//O(E)
		{
			int prefix = ( state + 1 ) < m ? ( state + 1 ) : m;
			while( prefix > 0 )//O(M)
			{
				if( prefix == 1 && pattern[prefix-1] == alphabets[j] )
					break;
				if( pattern[prefix-1] == alphabets[j] && compare( pattern , state - 1 , prefix - 2 ) == 1 )//O(M)
					break;
				prefix--;					
			}
			transition_table[state][j] = prefix;
		}
	}
}

int compare( char pattern[] , int state , int prefix )
{
	while( prefix >= 0 && state >= 0 )
		if( pattern[prefix--] != pattern[state--] )
			return -1;
	return 1;
}
		
	
	
	
	

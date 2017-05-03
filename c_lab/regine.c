#include <stdio.h>
#include <stdlib.h>
#define MAXN 10
int x[ MAXN ]; /* solution vector */
int n; /* chessboard size */
int solNb;  /* solution number */
enum { FALSE, TRUE };

int phi( int k )
{
    int i;
    for(i=1; i<k; i++)
    {
        if(x[i]==x[k])return FALSE;
        else if(abs(k-i)==abs(x[k]-x[i]))return FALSE;
    }
    return TRUE;
}

void displaySolution()
{
    solNb++;
    printf( "\nSolution %d:\n", solNb );
    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
            if(j != x[i]) printf(".");
            else printf("R");
        printf("\n");
    }
}


void recQueens( int k )
{
    int j;
    for ( j = 1; j <= n; j++ )
    {
        x[ k ] = j;
        if ( phi( k ) == TRUE)
        {
            if ( k < n )
                recQueens( k + 1 );
            else
                displaySolution();
        }
    }
}
int main()
{
    printf( "\nNumber of queens=" );
    scanf( "%d", &n );
    solNb = 0;
    recQueens( 1 );
    printf( "\nEnd." );
    return 0;
}


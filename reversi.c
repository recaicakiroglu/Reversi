#include <stdio.h>
#include <stdlib.h>
#define BLACK  1
#define NONE   0
#define WHITE -1
 
int** arena;                      
int dimension;            
int actual = BLACK;
int ctr;
             
void opening ( const int n );
void finalize ( );
void showing ( );
int fo2 ( const int m, const int n );
int turning ( int m, int n );
int winner ( );
 
             
int main ( int argc, char** argv ) {
        int pr;        
        int m, n;  
        int final1 = 1;
                if ( argc >= 2 )
                                {
                if ( sscanf(argv[1], "%d", &pr) <= 0 )
                                     {
                printf("Invalid number of command line arguments\n", argv[1]);
                        exit(1);
                     }              
                                if(pr%2==0 && pr>=4)
                {
                                opening(pr);
                                }
                else  
                {      
                printf("Invalid format for command line arguments. The size argument should be an even positive integer number greater then or equal to 4");  
                exit(1);  
			    }                                                                      
                }
        else {
                opening(8);  
        }
        while ( final1 > 0 ) {
                showing();
 
                        if ( actual == BLACK )
                                                {
                                printf("Player 1's turn:");
                        }
                        else
                                                {
                                printf("Player 2's turn:");
                        }
                        while ( 1 )
                                                {
                                printf(" ");
                                fflush(stdin);
                                if ( scanf("%d", &m)<0 || scanf("%d", &n)<0 )
                                {  
                                        printf("Invalid move. Please make another move\n");                              
                                        continue;
                                }
                                final1 = turning(n, m);
                                if ( final1 == 0 )
                                                                {
                                        printf("Invalid move. Please make another move\n", m, n);
                                }
                                else {
                                        break;
                                }
                        }
        }
 
        showing();
        switch ( winner() ) {
                case BLACK: printf("Game Ended...");
                                break;
                case WHITE: printf("Game Ended...");
                                break;
                case NONE : printf("Game Ended...");
                                break;
        }
 
        finalize();
        return 0;
}
 
void opening ( const int n ) {
       
 
        int i, j;
 
                arena = (int**)malloc( sizeof(int*) * n );
        for ( i=0; i < n; i++ )
                {
                arena[i] = (int*)malloc( sizeof(int) * n );
                for ( j=0; j < n; j++ )
                                {
                        arena[i][j] = NONE;
                }
        }
        arena[n/2-1][n/2-1] = WHITE;
        arena[n/2-1][n/2]   = BLACK;
        arena[n/2][n/2-1]   = BLACK;
        arena[n/2][n/2]     = WHITE;
 
                dimension = n;
}
 
 
void finalize ( )
{
       
        int i;
        for ( i=0; i < dimension; i++ )
            {
                free(arena[i]);
        }
        free(arena);
}
 
 
void showing ( )
{
       
     
        int i, j;
        for ( i=0; i < dimension-1; i++ )
                 {
                  printf("  ");
                 }
        printf("\n");
       
        for ( i=0; i < dimension; i++ ) {
               
                for ( j=0; j < dimension; j++ )
                                 {
                        switch ( arena[j][i] )
                                                 {
                                case BLACK: printf("X");
                                            break;
                                case WHITE: printf("0");
                                            break;
                                case NONE : printf("-");
                                            break;
                        }
                        printf(" ");
                }
                printf("\n");
                if ( i < dimension-1 )
                                {
                        printf("  ");
                        for ( j=0; j < dimension-1; j++ )
                                                 {
                                printf("");
                        }
                        printf("\n");
                }
        }
 
        printf("  ");
        for ( i=0; i < dimension-1; i++ )
                 {
                 printf("");
                 }
        printf("\n");
}
 
 
int fo2 ( const int m, const int n )
{
                int i, j;
        int final1 = 0;
        int ctr = 0;  
     
 
 
        if ( m < 0 || dimension <= m || n < 0 || dimension <= n ) return 0;
        if ( arena[m][n] != NONE ) return 0;
       
       
        if ( n > 1 && arena[m][n-1] == -actual )
                 {            
                 for ( j=n-2; j >= 0; j-- )
                 {
                        if ( arena[m][j] == actual )
                                                {
                                                final1 += 1; ctr += n-j-1; break;
                                                }
                        if ( arena[m][j] == NONE    )
                                                 {
                                                 break;
                                                 }
                }
        }
       
 
        if ( n < dimension-2 && arena[m][n+1] == -actual )
                {  
                for ( j=n+2; j < dimension; j++ )
                                {
                        if ( arena[m][j] == actual )
                                                {
                                                 final1 += 2; ctr += j-n-1; break;
                                                 }
                        if ( arena[m][j] == NONE    )
                                                {
                                                break;
                                                }
                }
        }
       
                if ( m > 1 && arena[m-1][n] == -actual )
                                 {          
                                    for ( i=m-2; i >= 0; i-- )
                                 {
                        if ( arena[i][n] == actual )
                                                {
                                                final1 += 4; ctr += m-i-1; break;
                                                 }
                        if ( arena[i][n] == NONE    )
                                                {
                                                break;
                                                 }
                }
        }
 
       
        if ( m < dimension-2 && arena[m+1][n] == -actual )
                 {  
                for ( i=m+2; i < dimension; i++ )
                                {
                        if ( arena[i][n] == actual)
                                                 {
                                                  final1 += 8; ctr += i-m-1; break;
                                                 }
                        if ( arena[i][n] == NONE)
                                                {
                                                break;
                                            }
                }
        }
 
 
        if ( m > 1 && n > 1 && arena[m-1][n-1] == -actual )
                 {  
                for ( i=m-2, j=n-2;  i>=0 && j>=0;  i--, j-- )
                                 {
                        if ( arena[i][j] == actual )
                                                 {
                                                  final1 += 16; ctr += n-j-1; break;
                                                 }
                        if ( arena[i][j] == NONE    )
                                                {
                                                break;
                                             }
                }
        }
       
 
        if ( m < dimension-2 && n > 1 && arena[m+1][n-1] == -actual ) {             for ( i=m+2, j=n-2;  i<dimension && j>=0;  i++, j-- ) {
                        if ( arena[i][j] == actual ) { final1 += 32; ctr += n-j-1; break; }
                        if ( arena[i][j] == NONE    ) { break; }
                }
        }
 
 
        if ( m > 1 && n < dimension-2 && arena[m-1][n+1] == -actual ) {             for ( i=m-2, j=n+2;  i>=0 && j<dimension;  i--, j++ ) {
                        if ( arena[i][j] == actual ) { final1 += 64; ctr += j-n-1; break; }
                        if ( arena[i][j] == NONE    ) { break; }
                }
        }
       
                if ( m < dimension-2 && n < dimension-2 && arena[m+1][n+1] == -actual ) {                for ( i=m+2, j=n+2;  i < dimension && j < dimension;  i++, j++ ) {
                        if ( arena[i][j] == actual ) { final1 += 128; ctr += j-n-1; break; }
                        if ( arena[i][j] == NONE    ) { break; }
                }
        }
 
 
        return final1;
}
 
 
 
int turning ( int m, int n ) {
       
     
        int i, j;
        int turned = 0;
        int fo1 = fo2(m, n);
 
        if ( !fo1 ) return 0;
 
        arena[m][n] = actual;
 
 
       
        if ( fo1 & 1 ) {
                for ( j=n-1;  arena[m][j] == -actual;  j-- ) {
                        arena[m][j] = actual;
                        turned++;
                }
        }
        fo1 >>= 1;
       
                if ( fo1 & 1 ) {
                for ( j=n+1;  arena[m][j] == -actual;  j++ ) {
                        arena[m][j] = actual;
                        turned++;
                }
        }
        fo1 >>= 1;
       
 
        if ( fo1 & 1 ) {
                for ( i=m-1;  arena[i][n] == -actual;  i-- ) {
                        arena[i][n] = actual;
                        turned++;
                }
        }
        fo1 >>= 1;
 
 
        if ( fo1 & 1 ) {
                for ( i=m+1;  arena[i][n] == -actual;  i++ ) {
                        arena[i][n] = actual;
                        turned++;
                }
        }
        fo1 >>= 1;
 
       
        if ( fo1 & 1 ) {
                for ( i=m-1, j=n-1;  arena[i][j] == -actual;  i--, j-- ) {
                        arena[i][j] = actual;
                        turned++;
                }
        }
        fo1 >>= 1;
       
       
        if ( fo1 & 1 ) {
                for ( i=m+1, j=n-1;  arena[i][j] == -actual;  i++, j-- ) {
                        arena[i][j] = actual;
                        turned++;
                }
        }
        fo1 >>= 1;
 
 
        if ( fo1 & 1 ) {
                for ( i=m-1, j=n+1;  arena[i][j] == -actual;  i--, j++ ) {
                        arena[i][j] = actual;
                        turned++;
                }
        }
        fo1 >>= 1;
       
 
        if ( fo1 & 1 ) {
                for ( i=m+1, j=n+1;  arena[i][j] == -actual;  i++, j++ ) {
                        arena[i][j] = actual;
                        turned++;
                }
        }
        fo1 >>= 1;
 
        actual = -actual;
       
 
        for ( i=0; i < dimension; i++ ) {
                for ( j=0; j < dimension; j++ ) {
                        if ( fo2(i, j) ) {
                                return turned;                                }
                }
        }
 
 
        actual = -actual;
        for ( i=0; i < dimension; i++ ) {
                for ( j=0; j < dimension; j++ ) {
                        if ( fo2(i, j) ) {
                                return turned;
                        }
                }
        }
       
       
        return -1;
}
 
 
 
int winner ( ) {
       
       
        int i, j;
        int t = 0, ctr=0, blank=0;
     
 
 
        for ( i=0; i < dimension; i++ ) {
                for ( j=0; j < dimension; j++ ) {
                        t += arena[i][j];
                        if(arena[i][j]==BLACK) ctr++;
                        else if(arena[i][j]==NONE) blank++;
                }
        }
        printf("Player 1 : %d\nPlayer 2 : %d \n", ctr, dimension*dimension-ctr-blank);
       
        if      ( t < 0 ) return WHITE;
        else if ( t > 0 ) return BLACK;
        else              return NONE;
}


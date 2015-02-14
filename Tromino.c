/*
This code can be found in
http://condor.depaul.edu/mkalin/cse/tromino.c
and this is not written by me. 
I just uploaded the code here to use as a reference.

This program tiles with right trominoes an nxn
board with one square missing, assuming that n
is a power of 2.                                */

#include <stdio.h>
#include <stdlib.h>

void tromino /* function to do tiling */
     ( int x_board,      /* x coordinate of board */
       int y_board,      /* y coordinate of board */
       int x_missing,    /* x coordinate of missing square */
       int y_missing,    /* y coordinate of missing square */
       int board_size ); /* size of board */


main()
{
     int board_size,
         x_missing,  /* x coordinate of missing square */
         y_missing;  /* y coordinate of missing square */
     do {
          printf( "\n-------------------------------------" );
          printf( "\nEnter size of board (0 to quit): " );
          scanf( "%d", &board_size );
          if ( board_size ) {
               printf( "\nEnter coordinates of missing square: " );
               scanf( "%d%d", &x_missing, &y_missing );
               printf( "\n\nTiling\n------\n" );
               tromino( 0, 0, x_missing, y_missing, board_size );
          }
     } while ( board_size );

     return EXIT_SUCCESS;
}

void tromino( int x_board,     /* x coordinate of board */
              int y_board,     /* y coordinate of board */
              int x_missing,   /* x coordinate of missing square */
              int y_missing,   /* y coordinate of missing square */
              int board_size ) /* size of board */
{
     int half_size = board_size/2, /* size of subboard */
         x_center,  /* x coordinate of center of board */
         y_center,  /* y coordinate of center of board */
         x_upper_left,  /* x coordinate of missing square in upper 
                                                     left subboard */
         y_upper_left,  /* y coordinate of missing square in upper 
                                                     left subboard */
         x_upper_right, /* x coordinate of missing square in upper 
                                                    right subboard */
         y_upper_right, /* y coordinate of missing square in upper 
                                                    right subboard */
         x_lower_right, /* x coordinate of missing square in lower 
                                                    right subboard */
         y_lower_right, /* y coordinate of missing square in lower 
                                                    right subboard */
         x_lower_left,  /* x coordinate of missing square in lower 
                                                     left subboard */
         y_lower_left;  /* y coordinate of missing square in lower 
                                                     left subboard */

     if ( board_size == 2 ) {   /* 2x2 board */
          /* print position of tromino */
          printf( "%d %d ", x_board + 1, y_board + 1 );
          /* find and print orientation of tromino */
          if ( x_board == x_missing )
               /* missing square in left half */
               if ( y_board == y_missing )
                    /* missing square in lower left */
                    printf( "UR\n" );
               else
                    /* missing square in upper left */
                    printf( "LR\n" );
          else
               /* missing square in right half */
               if ( y_board == y_missing )
                    /* missing square in lower right */
                    printf( "UL\n" );
               else
                    /* missing square in upper right */
                    printf( "LL\n" );
          return;
     }

     /* compute x and y coordinates of center of board */
     x_center = x_board + half_size;
     y_center = y_board + half_size;

     /* print position of special, center tromino */
     printf( "%d %d ", x_center, y_center );

     /* Find and print orientation of center tromino.
        Also, set x_upper_left, y_upper_left, ... .  */
     if ( x_missing < x_center) {
          /* missing square in left half */
          x_upper_right = x_lower_right = x_center;
          y_upper_right = y_center;
          y_lower_right = y_center - 1;
          if ( y_missing < y_center ) {
               /* missing square in lower left quadrant */
               printf( "UR\n" );
               x_upper_left = x_center - 1;
               y_upper_left = y_center;
               x_lower_left = x_missing;
               y_lower_left = y_missing;
          }
          else {
               /* missing square in upper left quadrant */
               printf( "LR\n" );
               x_upper_left = x_missing;
               y_upper_left = y_missing;
               x_lower_left = x_center - 1;
               y_lower_left = y_center - 1;
          }
     }
     else {
          /* missing square in right half */
          x_upper_left = x_lower_left = x_center - 1;
          y_upper_left = y_center;
          y_lower_left = y_center - 1;
          if ( y_missing < y_center ) {
               /* missing square in lower right quadrant */
               printf( "UL\n" );
               x_upper_right = x_center;
               y_upper_right = y_center;
               x_lower_right = x_missing;
               y_lower_right = y_missing;
          }
          else {
               /* missing square in upper right quadrant */
               printf( "LL\n" );
               x_upper_right = x_missing;
               y_upper_right = y_missing;
               x_lower_right = x_center;
               y_lower_right = y_center - 1;
          }
     }

     /* tile the four subboards */
     tromino( x_board, y_board + half_size, 
          x_upper_left, y_upper_left, half_size );
     tromino( x_board + half_size, y_board + half_size, 
          x_upper_right, y_upper_right, half_size );
     tromino( x_board + half_size, y_board, 
          x_lower_right, y_lower_right, half_size );
     tromino( x_board, y_board, 
          x_lower_left, y_lower_left, half_size );
}
#define TRUE 1
#define FALSE 0

#include <stdlib.h>
#include <stdio.h>
#include "sudoku.h"
#include "solve.h"


// This function gets called recusive to bute force a solution
int solve(char ** game, int n) {
    show_game(game);
    // Find the next empty field 
    int x, y;
    int empty_x = -1;
    int empty_y = -1;
    int stop = FALSE; // To brak out of a nested loop

    for (y = 0; y < 9 && (stop == FALSE); y++ ) {
        for (x = 0; x < 9 && (stop == FALSE); x++) {
            if (game[y][x] == 0) {
                empty_x = x;
                empty_y = y;
                stop = TRUE;
            }
        }
    }
    
    // If no field is empty that means the grid is solved
    if (empty_x == -1 && empty_y == -1) return TRUE;

    // Get the box from the empty flield
    int empty_box = -1;
    empty_box = get_box_num(empty_x, empty_y);
    
    // If game is not filed yet go through every number and chek if 
    // it could be in the empty field
    int val;
    for (val = 1; val <= 9; val++) {
        int in_row = val_in_row(game, empty_y, val);
        int in_col = val_in_col(game, empty_x, val);
        int in_box = val_in_box(game, empty_box, val);
        //printf("Valid: %d %d %d %d\n", val, in_row, in_col, in_box);
        // If everything is false then the value 
        // can be placed in the empty field
        if (in_row == FALSE && in_col == FALSE && in_box == FALSE) {
            game[empty_y][empty_x] = val;
            
            n ++;
            int possible = solve(game, n);
            
            if (possible == TRUE) {
                // If the game is possible (is solved) then
                // pass the result to the upper functions
                return TRUE;
            } else {
                // If the game is not possible then undo the 
                //change and go to the next value
                game[empty_y][empty_x] = 0;
            }

        }
    }

    // If function hasn't returned anything then no value could be placed
    // so game is unsolvable
    return FALSE;
    
}


int val_in_row(char ** game, int row, int val) {
    for (int x = 0; x < 9; x++) {
        if (game[row][x] == val) {
            return TRUE;
        }
    }
    return FALSE;
}

int val_in_col(char ** game, int col, int val) {
    for (int y = 0; y < 9; y++) {
        if (game[y][col] == val) {
            return TRUE;
        }
    }
    return FALSE;
}

int val_in_box(char ** game, int box, int val) {

    // box is in range from 0-8 box number is read left-right up-down
    
    // Calc the offset values
    int x_offset;
    int y_offset;

    x_offset = box % 3;
    if (box < 3) {
        y_offset = 0;
    } else if (box < 6) {
        y_offset = 1;
    } else {
        y_offset = 2;
    }

    // Check the box for the value
    if (game[0 + y_offset][0 + x_offset] == val) return TRUE;
    else if (game[1 + y_offset][0 + x_offset] == val) return TRUE;
    else if (game[2 + y_offset][0 + x_offset] == val) return TRUE;
    else if (game[0 + y_offset][1 + x_offset] == val) return TRUE;
    else if (game[1 + y_offset][1 + x_offset] == val) return TRUE;
    else if (game[2 + y_offset][1 + x_offset] == val) return TRUE;
    else if (game[0 + y_offset][2 + x_offset] == val) return TRUE;
    else if (game[1 + y_offset][2 + x_offset] == val) return TRUE;
    else if (game[2 + y_offset][2 + x_offset] == val) return TRUE;
    else return FALSE;

}   

int get_box_num(int x, int y) {
    int box = -1;
    if (x >= 0 && x <= 2 && y >= 0 && y <= 2) box = 0;
    if (x >= 3 && x <= 5 && y >= 0 && y <= 2) box = 1;
    if (x >= 6 && x <= 8 && y >= 0 && y <= 2) box = 2;
    if (x >= 0 && x <= 2 && y >= 3 && y <= 5) box = 3;
    if (x >= 3 && x <= 5 && y >= 3 && y <= 5) box = 4;
    if (x >= 6 && x <= 8 && y >= 3 && y <= 5) box = 5;
    if (x >= 0 && x <= 2 && y >= 6 && y <= 8) box = 6;
    if (x >= 3 && x <= 5 && y >= 6 && y <= 8) box = 7;
    if (x >= 6 && x <= 8 && y >= 6 && y <= 8) box = 8;

    return box;   
}
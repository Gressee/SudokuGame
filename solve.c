#define TRUE 1
#define FALSE 0

#include <stdlib.h>
#include <stdio.h>
#include "solve.h"


int check_solvable(char ** game) {
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

int val_in_box() {
    
}
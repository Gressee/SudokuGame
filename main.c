#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

// Init the array with the start sudoku field
char ** init_sudoku(char ** game) {
    
    //// allocate the memory for a array of pointers to arrays ////
    game = (char **) malloc(9 * sizeof(char * ));
    for (int row = 0; row < 9; row ++) {
        game[row] = (char * ) malloc(9 * sizeof(char));
    }

    //// create the sudoku values ////
    int x, y;
    for (y = 0; y < 9; y++) {
        for (x = 0; x < 9; x ++) {
            game[y][x] = 1;
        }
    }

    //// return the initialised game array pointer ////
    return game;
}

void show_game(char ** game) {
    int x, y, i;
    int width = 9*3 + 4;

    // print frist horizontal
    for (i = 0; i < width; i++) printf("-");
    printf("\n");

    // print first rows
    for (y = 0; y < 9; y ++) {
        
        // print horizontal lines every 3 lines
        if (y == 3 || y == 6 ) {
            for (i = 0; i < width; i++) printf("-");
            printf("\n");
        }
        
        // print first vertical line
        printf("|");

        // Print the line
        for (x = 0; x < 9; x++) {
            
            // print vertical line every 3 columns
            if (x == 3 || x == 6) { 
                printf("|");
            }

            // Print number (only if there is an entry, if not the the value in the array is 0)
            if (game[y][x] != 0) {
                printf(" %d ", game[y][x]);
            } else {
                printf("   ");
            }
        }

        // print last vertical line
        printf("|");

        // Go to the next line
        printf("\n");
    }

    // print bottom hoizontal line
    for (i = 0; i < width; i++) printf("-");
    printf("\n");

}

int check_solved(char ** game) {
    int x, y;
    int target = 1+2+3+4+5+6+7+8+9;
    int check, hor_solved, ver_solved, box_solved;
       
    hor_solved = 0;
    ver_solved = 0;
    box_solved = 0;
    
    // check hoizontal lines
    for (y = 0; y < 9; y++) {
        check = 0;
        for (x = 0; x < 9; x++) {
            check += game[y][x];
        }
        if (check == target) hor_solved ++;
    }

    // check vertical lines
    for (x = 0; x < 9; x++) {
        check = 0;
        for (y = 0; y < 9; y++) {
            check += game[y][x];
        }
        if (check == target) ver_solved ++;
    }

    // check solved boxes
    int start_x, start_y;
    check = 0;
    for (start_x = 0; start_x <= 6; start_x += 3) {
        for (start_y = 0; start_y <= 6; start_y += 3) {
            check = 0;

            check += game[start_y + 0][start_x + 0];
            check += game[start_y + 0][start_x + 1];
            check += game[start_y + 0][start_x + 2];
            check += game[start_y + 1][start_x + 0];
            check += game[start_y + 1][start_x + 1];
            check += game[start_y + 1][start_x + 2];
            check += game[start_y + 2][start_x + 0];
            check += game[start_y + 2][start_x + 1];
            check += game[start_y + 2][start_x + 2];

            if (check == target) box_solved ++;
        }
    }

    // chekc final solve 
    if (hor_solved == 9 || ver_solved == 9 || box_solved == 9) {
        return TRUE;
    } else {
        return FALSE;
    }
}



int main () {
    
    // Create the main array
    char ** game;

    game = init_sudoku(game);

    show_game(game);

    int s = check_solved(game);
    printf("\n%d\n", s);

    return 1;
}
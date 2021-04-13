#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku.h"
#include "solve.h"



// Copys game from one array to another
char ** copy_game_array(char ** source, char ** target) {
    for (int x = 0; x < 9; x ++) {
        for (int y = 0; y < 9; y++) {
            target[y][x] = source[y][x];
        }
    }
    return target;
}


// Init the array 
char ** init_sudoku_array(char ** array) {
    
    //// allocate the memory for the game array ////
    array = (char **) malloc(9 * sizeof(char * ));
    for (int row = 0; row < 9; row ++) {
        array[row] = (char * ) malloc(9 * sizeof(char));
    }

    //// return the initialised game array pointer ////
    return array;
}


// Generate the start
char ** generate_sudoku(char ** game) {
    // Init random number generation
    //srand((unsigned int)time(NULL));

    int clues = 25;
    int i, x, y, val;

    int possible = TRUE;
    int in_row, in_col, in_box;

    char ** test_game;
    test_game = init_sudoku_array(test_game);

    // Generate clues without checking if its solveable
    for (i = 0; i < clues; i++) {
        
        do {
            x = rand() % 9;
            y = rand() % 9;
            val = rand() % 9 + 1;

            // Check if value is possible in this field
            in_row = val_in_row(game, y, val);
            in_col = val_in_col(game, x, val);
            in_box = val_in_box(game, get_box_num(x, y), val);

            if (in_row == FALSE && in_col == FALSE && in_box == FALSE) {
                possible = TRUE;
            } else {
                possible = FALSE;
            }
        } while (game[y][x] != 0 || possible == FALSE);

        game[y][x] = val;
    }
    
    // Generate the new field aslong as the game is not solvable
    do {
        // Generate the new value
        val = rand() % 9 + 1;
        
        // Generate the new coords aslong as the space is already taken
        do {
            x = rand() % 9;
            y = rand() % 9;

            // Check if value is possible in this field
            in_row = val_in_row(game, y, val);
            in_col = val_in_col(game, x, val);
            in_box = val_in_box(game, get_box_num(x, y), val);

            if (in_row == FALSE && in_col == FALSE && in_box == FALSE) {
                possible = TRUE;
            } else {
                possible = FALSE;
            }

        } while (game[y][x] != 0 || possible == FALSE);
        
        // Set the new value
        game[y][x] = val;

        // copy game to a new array to test solve
        test_game = copy_game_array(game, test_game);

    } while (solve(test_game, 1) == FALSE);    
    
    return game;
}


// After game generation and check if possible get the fixed values
char ** get_fixed_values(char ** game, char ** fixed) {

    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            if (game[y][x] == 0) fixed[y][x] = 0; 
            else fixed[y][x] = 1;
        }
    }

    // retuen the fixed array
    return fixed;
}


// change the game array 
char ** get_user_action(char ** game, char ** fixed) {
    // get user input
    int x, y, value;
    printf(">>> ");
    scanf("%d:%d %d", &x, &y, &value);

    // change y and y so they start at 1
    x -= 1;
    y -= 1;

    // check if value is fixed
    if (fixed[y][x] == TRUE) {
        printf("This value can't be changed\n");
    } else {
        game[y][x] = value;
    }

    // return the new game array
    return game;
}


// Print game to console
void show_game(char ** game, char ** fixed) {
    int x, y, i;
    int width = 9*3 + 4;

    // Define Colorsets
    char * color_set;
    char c_normal[] = "\033[0m";
    char c_fixed[] = "\033[30;47m";
    char c_user_val[] = "\033[96m";

    printf("\n");

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
                if (fixed[y][x]) color_set = c_fixed;
                else color_set = c_user_val;

                printf(" %s%d%s ", color_set, game[y][x], c_normal);
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


// Check if the game is solved
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
    
    // create the main array that holds the values
    char ** game;
    game = init_sudoku_array(game);

    // crete the array that stores if a value is changeable
    char ** fixed;
    fixed = init_sudoku_array(fixed);

    // create the game
    game = generate_sudoku(game);
    fixed = get_fixed_values(game, fixed);
    
    // show the game for the first time
    show_game(game, fixed);

    int solved;
    while (TRUE) {
        game = get_user_action(game, fixed);
        show_game(game, fixed);
        solved = check_solved(game);
        

        if (solved == TRUE) {
            printf("You're Winner!!");
            break;
        }
    }
    
    return 1;
}



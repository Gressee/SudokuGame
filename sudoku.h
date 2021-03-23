#ifndef SUDOKU_H_
#define SUDOKU_H_

// declare all game functions
char ** copy_game_array(char ** source, char ** target);
char ** init_sudoku(char ** game);
char ** generate_sudoku(char ** game);
char ** get_fixed_values(char ** game, char ** fixed);
char ** get_user_action(char ** game, char ** fixed);
void show_game(char ** game);
int check_solved(char ** game);

#endif
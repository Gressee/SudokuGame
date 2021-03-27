#ifndef SOLVE_H_
#define SOLVE_H_

int solve(char ** game, int n);
int val_in_row(char ** game, int row, int val);
int val_in_col(char ** game, int col, int val);
int val_in_box(char ** game, int box, int val);
int get_box_num(int x, int y);


#endif 
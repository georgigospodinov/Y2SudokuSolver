#ifndef SUDOKU_H_MASTER_HEADER_GUARD
#define SUDOKU_H_MASTER_HEADER_GUARD

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int side;  // The side of a small square.
    int n;  // Largest number that can be written (side*side).
    int* grid;
}* Sudoku;

// The assigned 0 and 1 are used as booleans.
typedef enum {INVALID=-1, INCOMPLETE=0, COMPLETE=1} Status;

/* Function declarations: */

// Allocate and free memory.
Sudoku create_sudoku(int side);
Sudoku copy_sudoku(Sudoku src);
void free_sudoku(Sudoku s);

// IOs.
void print_sudoku(Sudoku s);
void scan_sudoku(Sudoku s);

// Cell accessors.
int get_value_at(Sudoku s, int row, int col);
void set_value_at(Sudoku s, int row, int col, int v);

// Checks.
Status check_list(int* list, int length);
void copy_row(Sudoku s, int r, int* row);
void copy_col(Sudoku s, int c, int* col);
void copy_square(Sudoku s, int q, int* square);
Status check_sudoku(Sudoku s);

#endif	// SUDOKU_H_MASTER_HEADER_GUARD

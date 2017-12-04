#ifndef ADV_SUDOKU_H_MASTER_HEADER_GUARD
#define ADV_SUDOKU_H_MASTER_HEADER_GUARD

#include <stdio.h>
#include <stdlib.h>

// Used to track if the algorithm is making progress with each loop.
short progress;

typedef struct {
    short* values;
    short amount;
}* Cell;

/* Cell function declarations: */
Cell create_cell(short size);
void free_cell(Cell c);
void store_value(Cell c, short v);
void remove_value(Cell c, short v);
void remove_all(Cell c, short length, short* values_to_remove);
void filter(Cell c, short length, short* values_to_keep);
short get_value(Cell c);  //If there is one value, return that, else 0.
void print_cell(Cell c);
short contains(Cell c, short l, short* v);
short contains_exactly(Cell c, short l, short* v);
short have_same_values(Cell c1, Cell c2);

short N, SIDE;
typedef struct {
    Cell* grid;
}* Sudoku;

// The assigned 0 and 1 are used as booleans.
typedef enum {INVALID=-1, INCOMPLETE=0, COMPLETE=1} Status;

/* Sudoku function declarations: */

// Allocate and free memory.
Sudoku create_sudoku();
Sudoku copy_sudoku(Sudoku src);
void free_sudoku(Sudoku s);
void initial_fill(Sudoku s);

// IOs.
void print_sudoku(Sudoku s);
void scan_sudoku(Sudoku s);

// Cell accessors.
Cell get_cell_at(Sudoku s, short r, short c);
short get_value_at(Sudoku s, short r, short c);
// Do I need any?

// Checks.
Status check_list(Cell* cells);
void copy_row(Sudoku s, short r, Cell* row);
void copy_col(Sudoku s, short c, Cell* col);
void copy_square(Sudoku s, short q, Cell* square);
Status check_sudoku(Sudoku s);
Sudoku copy_sudoku(Sudoku s);
//short are_same(Sudoku s1, Sudoku s2);

#endif /* ADV_SUDOKU_H_MASTER_HEADER_GUARD */

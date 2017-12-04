#ifndef TECHNIQUES_H_MASTER_HEADER_GUARD
#define TECHNIQUES_H_MASTER_HEADER_GUARD

#include "adv_sudoku.h"

void remark(Sudoku s);  // Simple marking.
void uniques(Sudoku s);  // Unique candidates.

// These two functions are used in both subsets and shared subgroups.
short undefined_values(Cell* cells, short* undetermined);
short find_indeces
    (Cell* cells, short l, short* v, short* indeces_buffer,
        short (*cont)(Cell, short, short*), short* accumulator);

void subset(Sudoku s);  // Naked and Hidden subsets.
void sharedsubgroups(Sudoku s);  // AKA row/column/block interactions.

// These two functions are used in both x-wing and sword-fish.
short arr_contains_v(short length, short* arr, short v);
short indeces_containing(Cell* cells, short v, short* indeces);
void remove_value_from_cells(Cell* cells, int value, short skip_l, short* skips);

void xwing(Sudoku s);  // X-Wing technique.
void swordfish(Sudoku s);  // Sword-fish technique.

#endif /* TECHNIQUES_H_MASTER_HEADER_GUARD */


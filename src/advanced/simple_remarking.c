#include "techniques.h"

// Reduce the possible values for a given cell.
void reduce_values(Sudoku s, short r, short c) {
    
    if(get_value_at(s, r, c)) return;  // Value already determined.
    Cell cell = get_cell_at(s, r, c);

    // Remove ones that appear in row r, col c.
    short v;
    for (short i = 0; i < N; i++) {
        if (i != c) {
            v = get_value_at(s, r, i);  // every other cell in the row
            if (v) remove_value(cell, v);
        }
        if (i != r) {
            v = get_value_at(s, i, c);  // every other cell in the column
            if (v) remove_value(cell, v);
        }
    }  // for
    
    // Remove values that appear in the square this cell belongs to.
    short square_r = (r/SIDE)*SIDE;
    short square_c = (c/SIDE)*SIDE;
    for (short i = square_r; i < square_r+SIDE; i++) {
        for (short j = square_c; j < square_c+SIDE; j ++) {
            if (i == r && j == c) continue;  // Skip current cell.
            
            v = get_value_at(s, i, j);
            if (v) remove_value(cell, v);
        }
    }  // for loops
    
}

// Put all values in every empty cell.
void initial_fill(Sudoku s) {
    
    for (short i = 0; i < N; i++) {
        for (short j = 0; j< N; j++) {
            if(get_value_at(s, i, j)) continue;  // Value is pre-set.
            // State that all values are possible.
            for (short v = 1; v <= N; v++) {
                Cell cell = get_cell_at(s, i, j);
                store_value(cell, v);
            }
        }
    }  // for loops
    
}

// Call reduce_values on all cells.
void remark(Sudoku s) {
    for (short i = 0; i < N; i++) {
        for (short j = 0; j< N; j++) {
            reduce_values(s, i, j);
        }
    }
}
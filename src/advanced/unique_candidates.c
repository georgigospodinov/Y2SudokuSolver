#include "techniques.h"

// Search for v in cells.
short find_index(short l, Cell* cells, short v) {
    
    short index = -1;
    for (short i = 0; i < l; i++) {
        
        if (v == get_value(cells[i])) return -1;  // Value is already set.
        if (get_value(cells[i])) continue;  // Skip filled cells.
        if (contains(cells[i], 1, &v) == 0)  continue;
         
        if (index == -1) index = i;  // Save the found index.
        else {
            index = -1;
            break;
        }
        
    }//for
    
    return index;

}

/* Given coordinates in a Sudoku and a value.
 * Write the value in those coordinates.
 * Remove it from all other cells in that row, column and square.
 */
void apply(Sudoku s, short r, short c, short v) {
    filter(get_cell_at(s, r, c), 1, &v);
    
    // Remove this value from all cells in row 'r'.
    for (short i = 0; i < N; i++) {
        if (i == c) continue;
        remove_value(get_cell_at(s, r, i), v);
    }
    
    // Remove this value from all cells in col 'c'.
    for (short i = 0; i < N; i++) {
        if (i == r) continue;
        remove_value(get_cell_at(s, i, c), v);
    }
    
    // Remove this value from all cells in its square.
    short start_r = (r/SIDE)*SIDE;
    short start_c = (c/SIDE)*SIDE;
    for (short i = start_r; i < start_r+SIDE; i++) {
        for (short j = start_c; j < start_c+SIDE; j++) {
            if (i == r && j == c) continue;
            remove_value(get_cell_at(s, i, j), v);
        }
    }
    
}

void uniques(Sudoku s) {
    
    Cell arr[N];
    short index;
    for (short i = 0; i < N; i++) {
        
        // For row 'i'.
        copy_row(s, i, arr);
        for (short v = 1; v <= N; v++) {
            index = find_index(N, arr, v);
            if (index != -1) apply(s, i, index, v);
        }
        
        // For col 'i'.
        copy_col(s, i, arr);
        for (short v = 1; v <= N; v++) {
            index = find_index(N, arr, v);
            if (index != -1) apply(s, index, i, v);
        }
        
        // For square 'i'.
        copy_square(s, i, arr);
        short square_r = (i/SIDE)*SIDE;
        short square_c = (i%SIDE)*SIDE;
        short cell_r, cell_c;  // row and col of a cell within square.
        for (short v = 1; v <= N; v++) {
            index = find_index(N, arr, v);
            if (index == -1) continue;
            
            cell_r = index/SIDE;
            cell_c = index%SIDE;
            apply(s, square_r+cell_r, square_c+cell_c, v);
        }
        
    }
}

#include "techniques.h"
/*
 * Given a list of cells and a value,
 * find the indeces of the ones that contain the value.
 * Return the number of indeces found.
 */
short indeces_containing(Cell* cells, short v, short* indeces) {
    
    short size = 0;
    for (short i = 0; i < N; i++) {
        
        // Ignore filled cells.
        if (get_value(cells[i])) continue;
        
        // Save indeces that contain the value.
        if (contains(cells[i], 1, &v)) indeces[size++] = i;
        
    }
    return size;
}

short arr_contains_v(short length, short* arr, short v) {
    for (short i = 0; i < length; i++) if (arr[i] == v) return 1;
    return 0;
}

void remove_value_from_cells(Cell* cells, int value, short skip_l, short* skips) {
    
    for (short i = 0; i < N; i++) {
        if (arr_contains_v(skip_l, skips, i)) continue;
        
        remove_value(cells[i], value);
    }
    
}

void find_and_clear_xwing(Sudoku s, short x, void (*copy1)(Sudoku, short, Cell*),
        void (*copy2)(Sudoku, short, Cell*)) {
    
    short first_indeces[N], second_indeces[N];
    short first_size, second_size;
    Cell first_arr[N], second_arr[N];
    Cell arr_to_clear[N];
    
    (*copy1)(s, x, first_arr);
    for (short v = 1; v <= N; v++) {
        
        first_size = indeces_containing(first_arr, v, first_indeces);
        
        // Only interested in pairs.
        if (first_size != 2) continue;
        
        // Find a list with the same value in the same indeces.
        for (short i = x+1; i < N; i++) {
            
            (*copy1)(s, i, second_arr);
            second_size = indeces_containing(second_arr, v, second_indeces);
            if (second_size != 2) continue;
    
            // Clear the occurrences of this value in that list.
            if (first_indeces[0] == second_indeces[0]
                    && first_indeces[1] == second_indeces[1]) {
                short skips[2] = {x, i};
                (*copy2)(s, first_indeces[0], arr_to_clear);
                remove_value_from_cells(arr_to_clear, v, 2, skips);
                
                (*copy2)(s, first_indeces[1], arr_to_clear);
                remove_value_from_cells(arr_to_clear, v, 2, skips);
            }
            
        }// for i = x+1
        
    }// for v
}

void xwing(Sudoku s) {
    
    for (short i = 0; i < N; i++) {
        
        // X-Wing with columns that have two locations for a value.
        find_and_clear_xwing(s, i, copy_col, copy_row);
        
        // X-Wing with rows that have two locations for a value.
        find_and_clear_xwing(s, i, copy_row, copy_col);
        
    }
    
}
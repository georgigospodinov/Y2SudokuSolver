/*
 * For any given value
 * Find N columns that that contain it in any number of cells less than N.
 * Do these indeces have N different values?
 * If so, clear those N rows of the value (skipping the columns).
 * Also applies for rows and columns the other way around.
 */
#include "techniques.h"

#define MAX_N 9*9
// ind_containing[i] contains the indeces at which 'v' appears in list 'i'.
static short ind_containing[MAX_N][MAX_N];
// size_of_ind[i] stores the size of ind_containing[i].
static short size_of_ind[MAX_N];
/*
 * Stores the indeces of the lists that contain 'v'.
 * AKA marks the indeces the algorithm is interested within the arrays above.
 */
static short lists_indeces[MAX_N];

static short alg_n;  // This stands for N.

short find_lists(Sudoku s, short v, void(*copy)(Sudoku, short, Cell*)) {
    
    short size = 0;
    
    Cell arr[N];
    for (short i = 0; i < N; i++) {
        (*copy)(s, i, arr);
        size_of_ind[i] = indeces_containing(arr, v, ind_containing[i]);
        if (0 < size_of_ind[i] && size_of_ind[i] <= alg_n) {
            lists_indeces[size++] = i;
        }
    }
    
    return size;
    
}

short are_there_N_values(short* buffer) {
    
    short size = 0;
    short index;
    for (short i = 0; i < alg_n; i++) {
        index = lists_indeces[i];
        for (short j = 0; j < size_of_ind[index]; j++) {
            if(arr_contains_v(size, buffer, ind_containing[index][j])) continue;
            buffer[size++] = ind_containing[index][j];
            if (size > alg_n) return 0;
            
        }
    }// for i, alg_n
    
    if (size == alg_n) return 1;
    else return 0;
    
}

void apply_sword_fish_with_v(Sudoku s, short v,
        void(*copy1)(Sudoku, short, Cell*),
        void(*copy2)(Sudoku, short, Cell*)) {
    
    if (find_lists(s, v, copy1) != alg_n) return;
    // Within these indeces, there must be exactly N that are different.
    short intersecting_lines[alg_n+1];  // And they get extracted here.
    if (!are_there_N_values(intersecting_lines)) return;
    for (short i = 0; i < alg_n; i++) {
            
        Cell arr[N];
        (*copy2)(s, intersecting_lines[i], arr);
        remove_value_from_cells(arr, v, alg_n, lists_indeces);
            
    }// for i
    
}

void swordfish(Sudoku s) {
    
    for (alg_n = 2; alg_n < N; alg_n++) {
        for(short v = 1; v <= N; v++) {
            apply_sword_fish_with_v(s, v, copy_col, copy_row);
            apply_sword_fish_with_v(s, v, copy_row, copy_col);
        }
    }
}
#undef MAX_N
#include "sudoku.h"

Sudoku create_sudoku(int side) {
    
    Sudoku s = (Sudoku) malloc(sizeof(Sudoku));
    s->side = side;
    s->n = side*side;
    
    s->grid = malloc(sizeof(int)*s->n*s->n);
    return s;
    
}

Sudoku copy_sudoku(Sudoku src) {
    
    Sudoku dest = (Sudoku) malloc(sizeof(Sudoku));
    dest->side = src->side;
    dest->n = src->n;
    dest->grid = malloc(sizeof(int)*dest->n*dest->n);
    for (int i = 0; i < dest->n; i++) {
        for (int j = 0; j < dest->n; j++) {
            set_value_at(dest, i, j, get_value_at(src, i, j));
        }
    }
    
    return dest;
}

void free_sudoku(Sudoku s) {
    free(s->grid);
    free(s);
}

void print_sudoku(Sudoku s) {
    int v;
    for ( int i = 0; i < s->n; i++ ) {
        printf(" ");  // Every line starts with a space.
        for ( int j = 0; j < s->n-1; j++ ) {
            v = get_value_at(s, i, j);
            if (v < 10) printf(" ");
            // Single digit numbers need a leading space.
            printf("%d ", v);
        }
        v = get_value_at(s, i, s->n-1);
        if (v > 9) printf("%d\n", v);
        else printf(" %d\n", v);
    }
}

void scan_sudoku(Sudoku s) {
    for (int i = 0; i < s->n; i++) {
        for (int j = 0; j < s->n; j++) {
            scanf(" %d", s->grid+(i*s->n)+j);
        }
    }
}

int get_value_at(Sudoku s, int row, int col) {
    return s->grid[row*(s->n) + col];
}

void set_value_at(Sudoku s, int row, int col, int v) {
    if (v >= 0 && v <= (s->n)) {
        s->grid[row*(s->n)+col] = v;
    }
}

Status check_list(int* list, int length) {
    
    // Each entry occurrences[i] says how many times i has been encountered.
    int occurrences[length+1];
    for (int i = 0; i <= length; i++)
        occurrences[i] = 0;
    
    for (int i = 0; i < length; i ++) {
        occurrences[list[i]]++;
        //Is it a repeat?
        if ( list[i] != 0 && occurrences[list[i]] > 1) return INVALID;
    }
    
    // If there are zeros, than the array is INCOMPLETE.
    if (occurrences[0]) return INCOMPLETE;
    else return COMPLETE;
    
}

// The third argument of the next three functions is the destination buffer.
void copy_row(Sudoku s, int r, int* row) {
    for (int i = 0; i < s->n; i++) {
        row[i] = get_value_at(s, r, i);
    }
}
void copy_col(Sudoku s, int c, int* col) {
    for (int i = 0; i < s->n; i++) {
        col[i] = get_value_at(s, i, c);
    }
}
void copy_square(Sudoku s, int q, int* square) {
    
    /* The two values are independent.
     * For a standard Sudoku, this sets the start row as 0, 3, or 6.
     * For a standard Sudoku, this sets the start column as 0, 3, or 6.
     * The different divisions allow access to the different squares.
     * More on this in the report.
     */
    int start_row = (q/s->side)*s->side;
    int start_col = (q%(s->side))*s->side;
    for (int i = 0; i < s->side; i++) {
        for (int j = 0; j < s->side; j++) {
            square[i*s->side+j] = get_value_at(s, start_row+i, start_col+j);
        }
    }
}

/* In check_sudoku(Sudoku s),
 * the following evaluation happens after every row/column/square check:
 * 
 * Call check_list with the array and the length (largest number);
 * If INVALID, exit immediately.
 * If the current status is 1 (COMPLETE),
 *  overwrite it with the returned status.
 * 
 * Why this is not a function? - See report.
 */
#define evaluate check_result = check_list(arr, s->n); if (check_result == INVALID) return INVALID; if (state) state = check_result
Status check_sudoku(Sudoku s) {
    
    Status state = COMPLETE; // Starting assumption.
    Status check_result;
    int arr[s->n];
    for (int i = 0; i < s->n; i++){
        copy_row(s, i, arr);
        evaluate;
        
        copy_col(s, i, arr);
        evaluate;
        
        copy_square(s, i, arr);
        evaluate;
    }
    
    return state;
}

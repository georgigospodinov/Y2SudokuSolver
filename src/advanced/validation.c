#include "techniques.h"

Status check_list(Cell* cells) {
    
    short occurrences[N+1];
    for (short i = 0; i <= N; i++) {
        occurrences[i] = 0;
    }
    
    short v;
    for (short i = 0; i < N; i++) {
        v = get_value(cells[i]);
        occurrences[v]++;
        if ( v != 0 && occurrences[v] > 1) return INVALID;
    }
    
    if (occurrences[0]) return INCOMPLETE;
    else return COMPLETE;
    
}

#define evaluate check_result = check_list(arr); if (check_result == INVALID) return INVALID; if (state) state = check_result
Status check_sudoku(Sudoku s) {
    
    Status state = COMPLETE; // Starting assumption.
    Status check_result;
    Cell arr[N];
    for (short i = 0; i < N; i++){
        copy_row(s, i, arr);
        evaluate;
        
        copy_col(s, i, arr);
        evaluate;
        
        copy_square(s, i, arr);
        evaluate;
    }
    
    return state;
}
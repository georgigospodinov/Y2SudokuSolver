#include "sudoku.h"

static int solutions;
static Sudoku ans;
void recursive_solve(Sudoku s) {

    if (solutions > 1) return;  // already MULTIPLE
    
    Status state = check_sudoku(s);
    if (state == INVALID) return;
    
    if (state == COMPLETE) {
        
        if (!solutions) ans = copy_sudoku(s);
        
        solutions ++;
        return;
    }
    
    /* Otherwise its INCOMPLETE.
     * 1. Find the first empty cell.
     * 2. Fill it with a number.
     * 3. Recurse.
     * Reasoning in report.
     */
    Sudoku working_copy = copy_sudoku(s);
    int r, c;
    for (r = 0; r < s->n; r++) {
        for (c = 0; c < s->n; c++) {
            if (get_value_at(working_copy, r, c) == 0) {
                goto recurse;  // Using goto to escape both loops.
            }
        }
    }
    
    // Try all values recursively.
    recurse:
    for (int v = 1; v <= s->n; v++) {
        set_value_at(working_copy, r, c, v);
        recursive_solve(working_copy);
        if (solutions > 1) return;  // already MULTIPLE
    }
    free_sudoku(working_copy);
    
}

int main (void) {
    
    // Read user input
    Sudoku s;
    int side;
    scanf("%d", &side);
    s = create_sudoku(side);
    scan_sudoku(s);
    
    // Solve
    recursive_solve(s);
    free_sudoku(s);
    
    // Print result
    if (solutions == 1) {
        print_sudoku(ans);
        free_sudoku(ans);
    } else if (solutions > 1) {
        printf("MULTIPLE\n");
        free_sudoku(ans);
    } else printf("UNSOLVABLE\n");
    
    return 0;
}
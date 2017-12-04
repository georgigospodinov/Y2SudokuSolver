#include "techniques.h"

void apply_techniques(Sudoku s) {
    
    do {
        do {
            do {
                do {
                    do {
                        progress = 0;
                        remark(s);
                    }
                    while(progress);

                    do {
                        progress = 0;
                        uniques(s);
                    }
                    while (progress);

                    subset(s);
                } while (progress);

                xwing(s);
            } while (progress);
            
            swordfish(s);
        } while(progress);
        
        sharedsubgroups(s);
    } while(progress);
    
}

// An interesting cell is one with the least amounts of possible values.
void set_interesting_cell(Sudoku s, short* r, short* c) {
    short current_amount = N;
    Cell cell;
    for (short i = 0; i < N; i++) {
        for (short j = 0; j < N; j++) {
            cell = get_cell_at(s, i, j);
            if (get_value(cell)) continue;  // Filled cells are not interesting
            
            if (cell->amount <= current_amount) {
                *r = i;
                *c = j;
                current_amount = cell->amount;
            }
        }
    }
}

static int solutions=0;
static Sudoku ans;
void optimized_recursion(Sudoku s) {
    
    if (solutions > 1) return;
    
    Status state = check_sudoku(s);
    if (state == INVALID) return;
    if (state == COMPLETE) {
        if(!solutions) ans = copy_sudoku(s);
        solutions++;
        return;
    }
    
    short r, c;
    set_interesting_cell(s, &r, &c);
    Cell interest = get_cell_at(s, r, c);
    short v;
    for (short i = 0; i < interest->amount ; i++) {
        
        v = interest->values[i];
        Sudoku working_copy = copy_sudoku(s);
        filter(get_cell_at(working_copy, r, c), 1, &v);
        
        apply_techniques(working_copy);
        optimized_recursion(working_copy);
        free_sudoku(working_copy);
    
    }
    
}

int main (void) {
    // Read user input:
    Sudoku s;
    scanf("%d", &SIDE);
    N = SIDE*SIDE;
    s = create_sudoku();
    scan_sudoku(s);
    
    initial_fill(s);
    
    Status state = check_sudoku(s);
    if (state == INVALID) {
        printf("UNSOLVABLE\n");
        free_sudoku(s);
        return 1;
    }
    
    apply_techniques(s);
    optimized_recursion(s);
    
    if (solutions == 1) {
        print_sudoku(ans);
        free_sudoku(ans);
    } else if (solutions > 1) {
        printf("MULTIPLE\n");
        free_sudoku(ans);
    } else printf("UNSOLVABLE\n");
    
    free_sudoku(s);
    return 0;
}
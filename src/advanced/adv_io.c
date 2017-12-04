#include "adv_sudoku.h"

Cell create_cell(short size) {
    Cell c = (Cell) malloc(sizeof(Cell));
    c->amount = 0;
    c->values = malloc(sizeof(short)*size);
    return c;
}

void free_cell(Cell c) {
    free(c->values);
    free(c);
}

void store_value(Cell c, short v) {
    c->values[c->amount++] = v;
}

void remove_value(Cell c, short v) {
    short i;  // Look for the index of v.
    for (i = 0; i < c->amount; i++) {
        if (c->values[i] == v) break;
    }
    if (i == c->amount) return;  // No value to remove.
    
    progress = 1;  //there is some progress
    c->amount--;
    while(i < c->amount)
        c->values[i] = c->values[++i];
    
}

void remove_all(Cell c, short length, short* values_to_remove) {
    short do_remove;
    for (short i = 0; i < c->amount; i++) {
        do_remove = 0;
        for (short j = 0; j < length; j++) {
            if (c->values[i] == values_to_remove[j]) {
                do_remove = 1;
                break;
            }
        }
        
        if (do_remove) remove_value(c, c->values[i]);
    }
}

void filter(Cell c, short length, short* values_to_keep) {
    
    short do_remove;
    for (short i = c->amount-1; i >= 0; i--) {
        do_remove = 1;
        for (short j = 0; j < length; j++) {
            if (c->values[i] == values_to_keep[j]) {
                do_remove = 0;
                break;
            }
        }
        
        if (do_remove) remove_value(c, c->values[i]);
    }
}

short get_value(Cell c) {
    if (c->amount == 1) return c->values[0];
    else return 0;
}

void print_cell(Cell c) {
    short v = get_value(c);
    if (v < 10) printf(" ");  // Single digit numbers need a leading space.
    printf("%hd", v);
}

// Says how many of the values [v0 - v(l-1)], cell 'c' contains.
short contains(Cell c, short l, short* v) {
    
    short counter = 0;
    for (short i = 0; i < l; i++) {
        for (short j = 0; j < c->amount; j++) {
            if (c->values[j] == v[i]) {
                counter ++;
                break;
            }
        }
    }
    return counter;
    
}

short contains_exactly(Cell c, short l, short* v) {
    if (c->amount != l) return 0;
    // All values should match.
    for (short i = 0; i < c->amount; i++) if (c->values[i] != v[i]) return 0;
    return 1;
}

short have_same_values(Cell c1, Cell c2) {
    
    if (c1->amount != c2->amount) return 0;
    
    for (short i = 0; i < c1->amount; i++) {
        if (c1->values[i] != c2->values[i]) return 0;
    }
    
    return 1;
    
}

void show_cell(Cell c) {
    printf("amount=%hd: ", c->amount);
    for (short i = 0; i < c->amount; i++) {
        printf("%hd ", c->values[i]);
    }
    printf("\n");
}

Sudoku create_sudoku() {
    
    Sudoku s = (Sudoku) malloc(sizeof(Sudoku));
    s->grid = malloc(sizeof(Cell)*N*N);
    for (short i = 0; i < N; i++) {
        for (short j = 0; j < N; j++) {
            s->grid[i*N+j] = create_cell(N);
        }
    }
    
    return s;
    
}

Sudoku copy_sudoku(Sudoku s) {
    
    Sudoku copy = (Sudoku) malloc(sizeof(Sudoku));
    copy->grid = malloc(sizeof(Cell)*N*N);
    for (short i = 0; i < N; i++) {
        for (short j = 0; j < N; j++) {
            copy->grid[i*N+j] = create_cell(N);
            Cell src = get_cell_at(s, i, j);
            Cell dst = get_cell_at(copy, i, j);
            if (src->amount == 1) {
                store_value(dst, src->values[0]);
            }
        }//for j
    }//for i
    initial_fill(copy);
    return copy;
}

void free_sudoku(Sudoku s) {
    
    for (short i = 0; i < N; i++) {
        for (short j = 0; j < N; j++) {
            free_cell(get_cell_at(s, i, j));
        }
    }
    free(s->grid);
    free(s);
}

void print_sudoku(Sudoku s) {
    for (short i = 0; i < N; i++) {
        printf(" ");
        for (short j = 0; j < N-1; j++) {
            print_cell(get_cell_at(s, i, j));
            printf(" ");
        }
        print_cell(get_cell_at(s, i, N-1));
        printf("\n");
    }
}

void scan_sudoku(Sudoku s) {
    int v;
    for (short i = 0; i < N; i++) {
        for (short j = 0; j < N; j++) {
            scanf(" %d", &v);
            if (v) store_value(get_cell_at(s, i, j), v);
        }
    }
}

Cell get_cell_at(Sudoku s, short r, short c) {
    return s->grid[r*N+c];
}

short get_value_at(Sudoku s, short r, short c) {
    return get_value(get_cell_at(s, r, c));
}

void copy_row(Sudoku s, short r, Cell* row) {
    for (short i = 0; i < N; i++) {
        row[i] = get_cell_at(s, r, i);
    }
}

void copy_col(Sudoku s, short c, Cell* col) {
    for (short i = 0; i < N; i++) {
        col[i] = get_cell_at(s, i, c);
    }
}

void copy_square(Sudoku s, short q, Cell* square) {
    short start_row = (q/SIDE)*SIDE;
    short start_col = (q%(SIDE))*SIDE;
    short size = 0;
    for (short i = start_row; i < start_row+SIDE; i++) {
        for (short j = start_col; j < start_col+SIDE; j++) {
            square[size++] = get_cell_at(s, i, j);
        }
    }
}
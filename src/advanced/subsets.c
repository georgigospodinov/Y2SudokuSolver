/*
 * A generalisation of unique_candidates.c.
 * Rather than one value in one cell,
 * l values in l cells. 
 */
#include "techniques.h"

// Search for v0 - v(l-1) in the given n cells. Returns the size of indeces_buffer.
short find_indeces
    (Cell* cells, short l, short* v, short* indeces_buffer,
        short (*cont)(Cell, short, short*), short* accumulator) {

    short size = 0;
    short contained;
    
    for (short i = 0; i < N; i++) {
        if (get_value(cells[i])) continue;  // Skip filled cells.
    
        contained = (*cont)(cells[i], l, v);
        if (contained) {
            indeces_buffer[size++] = i;
            (*accumulator) += contained;
        }
    }
    return size;
    
}

/*
 * Given l cells and l values,
 * remove all other values from these cells
 * and remove these l values from the other cells.
 */
void apply_multiple(Cell* cells, short l, short* indeces, short* vs) {
    
    short filter_remove_flag;  // 1 = filter, 0 = remove
    // Remove all other values from these cells
    for (short i = 0; i < N; i++) {
        
        filter_remove_flag = 0;
        // If this i is in indeces, then cells[i] should be filtered.
        for (short j = 0; j < l; j++) {
            if (indeces[j] == i) {
                filter_remove_flag = 1;
                break;
            }
        }
        
        if (filter_remove_flag) filter(cells[i], l, vs);
        else remove_all(cells[i], l, vs);
        
    }
    
}

// returns the number of pairs *2
short generate_pairs(short n, short* vs, short* pairs_buffer) {
    
    short size = 0;
    for (short i = 0; i < n; i++) {
        for (short j = i+1; j < n; j++) {
            pairs_buffer[size++] = vs[i];
            pairs_buffer[size++] = vs[j];
        }
    }
    
    return size;
    
}

// returns the number of triples *3
short generate_triples(short n, short* vs, short* triples_buffer) {
    
    short size = 0;
    for (short i = 0; i < n; i++) {
        for (short j = i+1; j < n; j ++) {
            for (short k = j+1; k < n; k++) {
                triples_buffer[size++] = vs[i];
                triples_buffer[size++] = vs[j];
                triples_buffer[size++] = vs[k];
            }
        }
    }
    
    return size;
    
}

// No general recursion because too much memory.

// Given a list of cells, fill a buffer with all undetermined values.
// Return size of buffer.
short undefined_values(Cell* cells, short* undetermined) {
    
    short size = 0;
    short defined_flag;
    for (short v = 1; v <= N; v++) {
        defined_flag = 0;
        for (short i = 0; i < N; i++) {
            if (get_value(cells[i]) == v) {
                defined_flag = 1;
                break;
            }
        }
        
        if (!defined_flag) undetermined[size++] = v;
        
    }
    
    return size;
}

// Given a pair/triple, call find and apply
void search_and_apply(Cell* cells, short l, short* tuple) {
    
    short subset_size;
    short subset[N];
    short accumulator = 0;
    
    // Naked subset.
    subset_size = find_indeces
            (cells, l, tuple, subset, contains_exactly, &accumulator);
    if (subset_size == l) {
        apply_multiple(cells, l, subset, tuple);
        return;
    }
    
    // Hidden subset.
    accumulator = 0;
    subset_size = find_indeces(cells, l, tuple, subset, contains, &accumulator);
    if (subset_size == l && accumulator == l*l)
        apply_multiple(cells, l, subset, tuple);
    
}

void work(Cell* cells) {
    
    short values[N];
    short un_values = undefined_values(cells, values);
    short pairs[N*(N-1)];
    short num_pairs = generate_pairs(un_values, values, pairs);
    for (short j = 0; j < num_pairs; j+=2) {
        search_and_apply(cells, 2, pairs+j);
    }
    un_values = undefined_values(cells, values);

    short triples[N*(N-1)*(N-2)/2];
    short num_triples = generate_triples(un_values, values, triples);
    for (short j = 0; j < num_triples; j+=3) {
        search_and_apply(cells, 3, triples+j);
    }
    
}

void subset(Sudoku s) {

    Cell arr[N];
    for (short i = 0; i < N; i++) {
        copy_row(s, i, arr);
        work(arr);
        
        copy_col(s, i, arr);
        work(arr);
        
        copy_square(s, i, arr);
        work(arr);
    }
}
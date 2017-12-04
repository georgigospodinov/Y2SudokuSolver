#include "techniques.h"

// Returns the square the indeces belong to. -1 if no such exists.
short convert_col_inds_to_square(short l, short col, short* cinds,
        short* indeces_buffer) {
    
    short first_square = (cinds[0]/SIDE)*SIDE + (col/SIDE);
    indeces_buffer[0] = (cinds[0]%SIDE)*SIDE + (col%SIDE);
    for (short i = 1; i < l; i++) {
        if ((cinds[i]/SIDE)*SIDE + (col/SIDE) != first_square) return -1;
        indeces_buffer[i] = (cinds[i]%SIDE)*SIDE + (col%SIDE);
    }
    
    return first_square;
}

short convert_row_inds_to_square(short l, short row, short* rinds,
        short* indeces_buffer) {
    
    short rpsms = (row%SIDE)*SIDE;  //Stands for RowPercentSideMultiplySide.
    short rdsms = (row/SIDE)*SIDE;  //Stands for RowDivideSideMultiplySide.
    
    short first_square = rdsms + (rinds[0]/SIDE);
    indeces_buffer[0] = rpsms + (rinds[0]%SIDE);
    for (short i = 1; i < l; i++) {
        if (rdsms + (rinds[i]/SIDE) != first_square) return -1;
        indeces_buffer[i] = rpsms + (rinds[i]%SIDE);
    }
    
    return first_square;
}

short convert_square_inds_to_row(short l, short squ, short* sinds,
        short* indeces_buffer) {
    
    short spsms = (squ%SIDE)*SIDE;  // Stands for SquarePercentSideMultiplySide.
    short sdsms = (squ/SIDE)*SIDE;  // Stands for SquareDivideSideMultiplySide.
    
    short first_row = sdsms + (sinds[0]/SIDE);
    indeces_buffer[0] = spsms + (sinds[0]%SIDE);
    for (short i = 1; i < l; i++) {
        if (sdsms + (sinds[i]/SIDE) != first_row) return -1;
        indeces_buffer[i] = spsms + (sinds[i]%SIDE);
    }
    
    return first_row;
}

short convert_square_inds_to_col(short l, short squ, short* sinds,
        short* indeces_buffer) {
    
    short spsms = (squ%SIDE)*SIDE;  // Stands for SquarePercentSideMultiplySide.
    short sdsms = (squ/SIDE)*SIDE;  // Stands for SquareDivideSideMultiplySide.
    
    short first_col = spsms + (sinds[0]%SIDE);
    indeces_buffer[0] = sdsms + (sinds[0]/SIDE);
    for (short i = 1; i < l; i++) {
        if (spsms + (sinds[i]%SIDE) != first_col) return -1;
        indeces_buffer[i] = sdsms + (sinds[i]/SIDE);
    }
    
    return first_col;
}

void clear_list(Cell* list, short value, short s, short* skips) {
    
    short clear_flag;
    for (short i = 0; i < N; i++) {
        
        clear_flag = 1;
        for (short j = 0; j < s; j++) {
            if (skips[j] == i) {
                clear_flag = 0;
                break;
            }
        }
        if (clear_flag) remove_value(list[i], value);
    }
    
}

void interaction(Sudoku s, short index, void (*copy)(Sudoku, short, Cell*),
        short value, short second_check,
        short (*convert)(short, short, short*, short*),
        void (*copy_crossover)(Sudoku, short, Cell*)) {
    
    short indeces[N];
    Cell list[N];
    (*copy)(s, index, list);
    short accumulator = 0;
    short size = find_indeces(list, 1, &value, indeces, contains, &accumulator);
    if(size==0) return;
    
    // Are the indeces aligned?
    
    if (size > SIDE) return;
    
    short crossover_indeces[size];
    short crossover = (*convert)(size, index, indeces, crossover_indeces);

    if (crossover == -1) return;
    
    Cell crosslist[N];
    (*copy_crossover)(s, crossover, crosslist);
    
    //clear crosslist of values, skip crossover_indeces
    clear_list(crosslist, value, size, crossover_indeces);
    remark(s);
    
    if (second_check == 0) return;
    
    // If second check is 1, than the case is square/column interaction.
    crossover = convert_square_inds_to_col
            (size, index, indeces, crossover_indeces);
    
    if (crossover == -1) return;
    
    copy_col(s, crossover, crosslist);
    clear_list(crosslist, value, size, crossover_indeces);
    remark(s);
    
}

void try_interactions_for_index(Sudoku s, short index) {
    
    Cell list[N];
    short missing[N];
    short amount;
    
    copy_row(s, index, list);
    amount = undefined_values(list, missing);
    for (short i = 0; i < amount; i++) {
        interaction(s, index, copy_row, missing[i],
                0, convert_row_inds_to_square, copy_square);
    }
    
    copy_col(s, index, list);
    amount = undefined_values(list, missing);
    for (short i = 0; i < amount; i++) {
        interaction(s, index, copy_col, missing[i],
                0, convert_col_inds_to_square, copy_square);
    }
    
    copy_square(s, index, list);
    amount = undefined_values(list, missing);
    for (short i = 0; i < amount; i++) {
        interaction(s, index, copy_square, missing[i],
                1, convert_square_inds_to_row, copy_row);
    }
    
}

void sharedsubgroups(Sudoku s) {
    for (short i = 0; i < N; i++) {
        try_interactions_for_index(s, i);
    }
}
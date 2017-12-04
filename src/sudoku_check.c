#include "sudoku.h"

int main (void) {
    int side;
    scanf("%d", &side);
    Sudoku s = create_sudoku(side);
    scan_sudoku(s);
    print_sudoku(s);
    
    Status state = check_sudoku(s);
    if (state == INVALID)
        printf("INVALID\n");
    else if (state == INCOMPLETE)
        printf("INCOMPLETE\n");
    else printf("COMPLETE\n");
    
    free_sudoku(s);
    return 0;
}
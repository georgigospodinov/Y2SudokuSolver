# Basic Requirements
out/sudoku_io.o: src/sudoku_io.c src/sudoku.h
	gcc src/sudoku_io.c -c -o out/sudoku_io.o -O3

out/sudoku_check.o: src/sudoku_check.c src/sudoku.h
	gcc src/sudoku_check.c -c -o out/sudoku_check.o -O3

out/sudoku_solve.o: src/sudoku_solve.c src/sudoku.h
	gcc src/sudoku_solve.c -c -o out/sudoku_solve.o -O3

sudoku_check: out/sudoku_check.o out/sudoku_io.o
	gcc out/sudoku_check.o out/sudoku_io.o -o sudoku_check

sudoku_solver: out/sudoku_solve.o out/sudoku_io.o
	gcc out/sudoku_solve.o out/sudoku_io.o -o sudoku_solver

# Extension

clean:
	rm -f out/*
	rm -f sudoku_check
	rm -f sudoku_solver


#include "sudoku.hpp"
#include "sudoku_utility.hpp"
#include "sudoku_zones.hpp"
#include "sudoku_seek.hpp"
#include <cstdlib>


int main(){

    Sudoku sudoku;
    Grid grid;
    int column, row;
    grid.x = 0; grid.y = 6;
    column = 6; row = 0; endline;

    zone_seek(sudoku, grid);
    std::cout << "-------------------------" << std::endl;
    column_seek(sudoku, grid, column);
    std::cout << "-------------------------" << std::endl;
    row_seek(sudoku, grid, row);

    return EXIT_SUCCESS;

}

/*

For each time it gets a solution print new Board to file(debug)

Easy Puzzle Thoughts

first row is missing 2, 5, 8
column 2 of first row cant be 2 because it already exists in the cross path
so check can it be 5, 8? in this case it cant be 5 because that also exists in cross path
so it must be 8

Implement basic cross-check per row cell, column cell
    cross out cells that cant have that missing number due to cross check

Implement basic zone-check per zone, relative to missing number
    cross out zones that cant have that missing number due to zone check


Hard Puzzle Thoughts

row 9 only missing 1 3 7
spot 1 can 1 or 3(after box checking) - not 7
spot 2 can 1 or 3 - not 7  
spot 3 can 1 or 7 - not 3 -- deduction makes spot 3 = 7

If no solution possible check Next row with the most amount of available numbers

cont.. 

First thing it should do is select one of the missing numbers to do a set of checks
Also need to pinpoint current cell

// need 1 2 3 4 5 6 7 8 9
// Available: 9 4 2 5 7 6
// Missing: 1 3 8

*/
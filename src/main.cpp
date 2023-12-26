#include "sudoku.hpp"
#include "sudoku_utility.hpp"
#include "sudoku_zones.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
using std::vector;



int main(){

    Sudoku sudoku;
    Grid grid;
    grid.x = 0; grid.y = 2;


    // Puzzle
    print_puzzle(sudoku);
    print_puzzle_row(sudoku, 0);
    print_puzzle_column(sudoku, 0);
    vector<int> whole_puzzle = puzzle_to_vector(sudoku);
    print_vector(whole_puzzle);

    // Row
    vector<int> row_numbers = get_row_numbers(sudoku, 0);
    print_vector(row_numbers);
    vector<int> row_missing = get_missing_numbers(row_numbers);

    // Column
    vector<int> column_numbers = get_column_numbers(sudoku, 7);
    print_vector(column_numbers);
    vector<int> column_missing = get_missing_numbers(column_numbers);

    // Zone
    int zone = get_zone(grid.x, grid.y);
    vector<int> zone_numbers = get_zone_numbers(sudoku, zone);
    print_zone_numbers(zone_numbers, zone);
    vector<int> zone_missing =get_missing_numbers(zone_numbers);

    column_crosscheck(sudoku, column_numbers, column_missing, 7);
    

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
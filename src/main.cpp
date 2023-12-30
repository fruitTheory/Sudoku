#include "sudoku.hpp"
#include "sudoku_utility.hpp"
#include "sudoku_zones.hpp"
#include "sudoku_seek.hpp"
#include <cstdlib>


int main(){

    Sudoku sudoku;
    Grid grid;
    int column, row;
    grid.x = 0; grid.y = 0;
    column = 0; row = 0; // endline;

    // zone_seek(grid);
    // std::cout << "-------------------------" << std::endl;
    // column_seek(column);
    // std::cout << "-------------------------" << std::endl;
    row_seek(row);
    

    return EXIT_SUCCESS;

}

/*

For each missing cell from avaiable numbers, check if first(1) missing number can be put in 
Check if it doesnt clash with the zone of current available numbers position 
Check if it doesnt clash with basic crosscheck then add it to a possibility vector
Then, if theres multiple possibilites in the vector, do a second crosscheck
This one with -1+1 neighbor columns/rows, to get probabilites
If the missing it found in neighbor cross checks, increase the probability
Then simply add the highest probable number in that slot
After this can implement backtrack method, for finalized solutions

For each time it gets a solution print new Board to file(debug)

Answers can come from deduction, as in other spots for sure cant be x missing number

*/
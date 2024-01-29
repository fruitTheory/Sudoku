#include "sudoku.hpp"
#include "sudoku_utility.hpp"
#include "sudoku_zones.hpp"
#include "sudoku_seek.hpp"
#include <cstdlib>


int main(){

    Sudoku sudoku;

    Grid grid;
    grid.x = 0; grid.y = 0;

    int column, row_iter;
    column = 0; row_iter = 2;

    sudoku.init_puzzle_status();

    for(int row_iter = 0; row_iter < 15; row_iter++){
        get_row_hits(row_iter);
        sudoku.push_cycle();
        sudoku.set_puzzle_status();
        //if(sudoku.get_cycles() % 9 == 0){ 
        //     vector p = puzzle_to_vector();
        //     store_puzzle(p); 
        // }
    }
    
    return EXIT_SUCCESS;

}
#include "sudoku.hpp"
#include "sudoku_utility.hpp"
#include "sudoku_zones.hpp"
#include "sudoku_solve.hpp"
#include <cstdlib>


int main(){

    Sudoku sudoku;

    int row_iter = 0;
    int running = 1;


    while(running){
        row_algorithm(row_iter);
        sudoku.push_cycle();
        ++row_iter;
        int solved = is_solved(Sudoku::puzzle);
        if(solved == 1){ running = 0; }
    }
    
    return EXIT_SUCCESS;

}

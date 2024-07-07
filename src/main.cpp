#include "sudoku.hpp"
#include "sudoku_utility.hpp"
#include "sudoku_zones.hpp"
#include "sudoku_solve.hpp"
#include <cstdlib>


int main(){

    Sudoku sudoku;

    int row_iter = 0;
    bool running = true;

    while(running){
        row_algorithm(row_iter);
        sudoku.push_cycle();
        ++row_iter;
        bool solved = is_solved();
        if(solved){ print_puzzle(); running = false; }
        if(Sudoku::backtrace){ running = false; }
    }
    
    if(Sudoku::backtrace){
        std::cout << "\n\n"
        << "Backtrace Algorithm: \n";
        solve_backtrace();
    }

    return EXIT_SUCCESS;

}

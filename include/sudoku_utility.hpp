#pragma once

#include "sudoku.hpp"
#include <iostream>
#include <vector>

void print_puzzle_row(Sudoku &sudoku, int row){
    printf("Selected row: %i\n", row);
    for(int x = 0; x < 9; x++){
        std::cout << sudoku.puzzle[row][x] << " ";
    } puts("\n");
}

void print_puzzle(Sudoku &sudoku){
    for(int y = 0; y < 9; y++){
        for(int x = 0; x < 9; x++){
            std::cout << sudoku.puzzle[y][x] << " ";
        } puts("");
    } puts("");
}

void print_vector(std::vector<int> &numbers){
    std::cout << "vector size: " << numbers.size() << std::endl;
    for(int x = 0; x < numbers.size(); x++){
        std::cout << numbers[x] << " ";
    } puts("");
}
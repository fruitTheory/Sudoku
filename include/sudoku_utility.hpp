#pragma once

#include "sudoku.hpp"
#include "config.hpp"
#include <iostream>
#include <vector>

// Prints single row from puzzle
void print_puzzle_row(Sudoku &sudoku, int row){
    printf("Selected row[%i]: \n", row);
    for(int x = 0; x < 9; x++){
        std::cout << sudoku.puzzle[row][x] << " ";
    } newline;
}

// Prints single column from puzzle
void print_puzzle_column(Sudoku &sudoku, int column){
    printf("Selected column[%i]: \n", column);
    for(int y = 0; y < 9; y++){
        std::cout << sudoku.puzzle[y][column] << " ";
    } newline;
}

// Prints pizzle array in a grid pattern
void print_puzzle(Sudoku &sudoku){
    for(int y = 0; y < 9; y++){
        for(int x = 0; x < 9; x++){
            std::cout << sudoku.puzzle[y][x] << " ";
        } newline;
    } newline;
}

// Prints any vector supplied
void print_vector(std::vector<int> &numbers){
    std::cout << "Vector size: " << numbers.size() << std::endl;
    for(int x = 0; x < (int)numbers.size(); x++){
        std::cout << numbers[x] << " ";
    } newline, newline;
}

// Prints supplied vector in a grid pattern
void print_zone_numbers(std::vector<int> &numbers, int zone){
    std::cout << "Zone: " << zone << std::endl;
    for(int x = 0; x < (int)numbers.size(); x++){
        std::cout << numbers[x] << " ";
        if((x+1) % 3 == 0){ newline; }
    } newline;
}
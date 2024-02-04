#include "sudoku_utility.hpp"
#include "Sudoku.hpp"
#include "config.hpp"
#include <iostream>
#include <vector>

// Prints single row from puzzle
void print_puzzle_row(int row){
    printf("Selected row[%i]: \n", row);
    for(int x = 0; x < 9; x++){
        std::cout << Sudoku::puzzle[row][x] << " ";
    } endline;
}

// Prints single column from puzzle
void print_puzzle_column(int column){
    printf("Selected column[%i]: \n", column);
    for(int y = 0; y < 9; y++){
        std::cout << Sudoku::puzzle[y][column] << " ";
    } endline;
}

// Prints whole puzzle in a grid pattern
void print_puzzle(){
    for(int y = 0; y < 9; y++){
        for(int x = 0; x < 9; x++){
            std::cout << Sudoku::puzzle[y][x] << " ";
        } endline;
    } endline;
}

// Prints whole puzzle in a grid pattern but takes an input
void print_puzzle_copy(std::array<std::array<int, 9>, 9> puzzle){
    for(int y = 0; y < 9; y++){
        for(int x = 0; x < 9; x++){
            std::cout << puzzle[y][x] << " ";
        } endline;
    } endline;
}

// Prints any pair vector supplied
void print_vector_pairs(std::vector<std::pair<int, int>> &numbers){
    std::cout << "Vector positions: " << std::endl;
    for(size_t x = 0; x < numbers.size(); x++){
        std::cout << numbers[x].first << numbers[x].second << " ";
    } endline, endline;
}

// Prints supplied vector in a grid pattern
void print_zone_numbers(std::vector<int> &numbers, int zone){
    std::cout << "Zone: " << zone << std::endl;
    for(size_t x = 0; x < numbers.size(); x++){
        std::cout << numbers[x] << " ";
        if((x+1) % 3 == 0){ endline; }
    } endline;
}
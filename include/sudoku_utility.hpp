#pragma once

#include <vector>
#include <iostream>

// Prints single row from puzzle
void print_puzzle_row(int row);

// Prints single column from puzzle
void print_puzzle_column(int column);

// Prints whole puzzle in a grid pattern
void print_puzzle();
void print_puzzle_status();

// Prints any vector/array supplied
template<typename T>
void print_vector(T &numbers){
    std::cout << "Vector size: " << numbers.size() << std::endl;
    for(size_t x = 0; x < numbers.size(); x++){
        std::cout << numbers[x] << " ";
    } std::cout << std::endl, std::cout << std::endl;
}

// Prints any pair vector supplied
void print_vector_pairs(std::vector<std::pair<int, int>> &numbers);

// Prints supplied vector in a grid pattern
void print_zone_numbers(std::vector<int> &numbers, int zone);
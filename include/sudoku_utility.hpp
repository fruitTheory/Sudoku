#pragma once

#include <vector>

// Prints single row from puzzle
void print_puzzle_row(int row);

// Prints single column from puzzle
void print_puzzle_column(int column);

// Prints whole puzzle in a grid pattern
void print_puzzle();

// Prints any integer vector supplied
void print_vector(std::vector<int> &numbers);

// Prints any pair vector supplied
void print_vector_pairs(std::vector<std::pair<int, int>> &numbers);

// Prints supplied vector in a grid pattern
void print_zone_numbers(std::vector<int> &numbers, int zone);
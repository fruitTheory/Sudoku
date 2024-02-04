#pragma once

#include <array>
#include <vector>
#include <utility>
using std::vector;
using std::array;
using std::pair;


class Sudoku{
    private:

    public:

        static int backtrace;
        static int cycles;
        inline void push_cycle(){ ++cycles; };

        static array<array<int, 9>, 9> puzzle;

        static inline void add_number(int y, int x, int number){
            Sudoku::puzzle[y][x] = number;
        }
};

// Position on grid (x, y)
struct Grid{
    int x;
    int y;
};

// Store current puzzle into a vector
vector<int> puzzle_to_vector();

// Gets numbers in a row and return a vector, rows start at 0
vector<int> get_row_numbers(int row, array<array<int, 9>, 9> &puzzle);

// Gets row positions and return a vector, rows start at 0
vector<pair<int, int>> get_row_positions(int row);

// Gets numbers in a column and return a vector, columns start at 0
vector<int> get_column_numbers(int column, array<array<int, 9>, 9> &puzzle);

// Gets column positions and return a vector, columns start at 0
vector<pair<int, int>> get_column_positions(int column);

/* Find and sort missing numbers from 'available numbers' and return a vector missing of numbers
Should be used in conjunction with functions that store available numbers into a vector */
vector<int> get_missing_numbers(vector<int> available_numbers);

// Make puzzle for faster copy paste
// Can take user input or hardcode puzzle key here
void make_puzzle();
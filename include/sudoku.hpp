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

        void run();

        static array<array<int, 9>, 9> puzzle;

        static inline void add_number(int y, int x, int number);

        int column, row;

};

// Position on grid (x, y)
struct Grid{
    int x;
    int y;
};

// Store current puzzle into a vector
vector<int> puzzle_to_vector();

// Gets numbers in a row and return a vector, rows start at 0
vector<int> get_row_numbers(int row);

// Gets row positions and return a vector, rows start at 0
vector<pair<int, int>> get_row_positions(int row);

// Gets numbers in a column and return a vector, columns start at 0
vector<int> get_column_numbers(int column);

// Gets column positions and return a vector, columns start at 0
vector<pair<int, int>> get_column_positions(int column);

void solve(Sudoku &sudoku, vector<int> &missing_numbers, vector<pair<int, int>> position);

// Cycles through empty spots in a column, does a cross check for each, meant for single column
void column_crosscheck(vector<int> &availabe_numbers, vector<int> &missing_numbers, int column);

/* Find and sort missing numbers from 'available numbers' and return a vector missing of numbers
Should be used in conjunction with functions that store available numbers into a vector */
vector<int> get_missing_numbers(vector<int> available_numbers);

// Check which column has least missing numbers, return the column number
void compare_columns();
// Check which row has least missing numbers, return the row number
void compare_rows();

// Make puzzle for faster copy paste
// Can take user input or hardcode puzzle key here
void make_puzzle();
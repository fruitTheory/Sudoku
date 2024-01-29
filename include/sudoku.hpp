#pragma once

#include <array>
#include <vector>
#include <utility>
using std::vector;
using std::array;
using std::pair;

// Later consier making puzzle private and have public methods to interact

class Sudoku{
    private:
        void init_status(){
            Sudoku::puzzle_status = Sudoku::puzzle;
            set_puzzle_status();
        }

    public:

        // Sudoku();

        void run();

        static int cycles;
        inline void push_cycle(){ ++cycles; };
        //inline int get_cycles(){ return cycles; }

        static array<array<int, 9>, 9> puzzle;
        static array<array<int, 9>, 9> puzzle_status;

        static inline void add_number(int y, int x, int number){
            Sudoku::puzzle[y][x] = number;
        }

        void set_puzzle_status();
        void init_puzzle_status(){ Sudoku::init_status(); }

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

/* Find and sort missing numbers from 'available numbers' and return a vector missing of numbers
Should be used in conjunction with functions that store available numbers into a vector */
vector<int> get_missing_numbers(vector<int> available_numbers);

// Make puzzle for faster copy paste
// Can take user input or hardcode puzzle key here
void make_puzzle();
#pragma once

#include "config.hpp"
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
using std::vector;
using std::array;
using std::pair;

class Sudoku{
    private:

    public:

        void run(){

        }

        // Easy
        array<array<int, 9>, 9> puzzle = {{
            { 4, 0, 0, 3, 0, 7, 6, 0, 0, },
            { 0, 0, 3, 0, 0, 2, 8, 0, 0, },
            { 0, 2, 8, 5, 1, 0, 7, 0, 4, },
            { 1, 0, 0, 8, 2, 3, 9, 0, 0, },
            { 0, 0, 0, 7, 5, 0, 1, 2, 8, },
            { 0, 0, 4, 0, 0, 9, 0, 0, 0, },
            { 6, 0, 2, 0, 4, 8, 3, 5, 1, },
            { 0, 3, 0, 0, 7, 0, 4, 0, 0, },
            { 0, 0, 9, 0, 0, 0, 2, 8, 0, },
        }};

        // Provide Column-y and Row-x to update puzzle with a number
        inline void add_number(Sudoku &sudoku, int y, int x, int number){
            sudoku.puzzle[y][x] = number;
        }

        int column, row;

};

// Position on grid (x, y)
struct Grid{
    int x;
    int y;
};

// Store current puzzle into a vector
vector<int> puzzle_to_vector(Sudoku &sudoku){
    vector<int> puzzle_numbers;
    // Interestingly due to how arrays stored this will loop through
    for(size_t x = 0; x < (sudoku.puzzle.size()); x++){
        puzzle_numbers.push_back(sudoku.puzzle[0][x]);
    }
    return puzzle_numbers;
}

// Gets numbers in a row and return a vector, rows start at 0
vector<int> get_row_numbers(Sudoku &sudoku, int row){
    std::vector<int> row_numbers;
    for(int x = 0; x < 9; x++){
        row_numbers.push_back(sudoku.puzzle[row][x]);
    }
    return row_numbers;
}

// Gets row positions and return a vector, rows start at 0
vector<pair<int, int>> get_row_positions(Sudoku &sudoku, int row){
    vector<pair<int, int>> row_coords;
    std::pair<int, int> coord;
    for(int x = 0; x < 9; x++){
        coord.first = x; coord.second = row;
        row_coords.push_back(coord);
    }
    return row_coords;
}

// Gets numbers in a column and return a vector, columns start at 0
vector<int> get_column_numbers(Sudoku &sudoku, int column){
    vector<int> column_numbers;
    for(int x = 0; x < 9; x++){
        column_numbers.push_back(sudoku.puzzle[x][column]);
    }
    return column_numbers;
}

// Gets column positions and return a vector, columns start at 0
vector<pair<int, int>> get_column_positions(Sudoku &sudoku, int column){
    vector<pair<int, int>> column_coords;
    std::pair<int, int> coord;
    for(int x = 0; x < 9; x++){
        coord.first = x; coord.second = column;
        column_coords.push_back(coord);
    }
    return column_coords;
}

void solve(Sudoku &sudoku, vector<int> &missing_numbers){
    int probability = 100/missing_numbers.size();
    std::cout << 100/missing_numbers.size(); endline;
    std::cout << missing_numbers[0]; endline;
    if(probability == 100){ sudoku.add_number(sudoku, 5, 6, missing_numbers[0]); }
}

// Cycles through empty spots in a column, does a cross check for each, meant for single column
void column_crosscheck(Sudoku &sudoku, vector<int> &availabe_numbers, vector<int> &missing_numbers, int column){
    
    array<vector<int>, 9> puzzle_rows;

    // Store vectors of rows into array
    for(int x = 0; x < 9; x++){
        std::cout << sudoku.puzzle[x][column] << " ";
        puzzle_rows[x] = get_row_numbers(sudoku, x);
    } endline;

    // Read vectors from array
    for(int x = 0; x < 9; x++){
        vector<int> current_vector = puzzle_rows[x];
        for(int value: current_vector){
            std::cout << value;
        } endline;
    } endline;

}

/* Finds missing numbers from any 'available numbers' input and returns a vector missing of numbers
Should be used in conjunction with functions that store available numbers into a vector */
vector<int> get_missing_numbers(vector<int> available_numbers){
    
    // need 1 2 3 4 5 6 7 8 9
    // Available: 9 4 2 5 7 6
    // Missing: 1 3 8
    vector<int> missing_numbers;
    vector<int> available_sorted;

    std::cout << "Available: ";

    // Manual sort - probably better to use stdlib - this uses a compare idea
    for(int y = 1; y <= 9; y++){
        for(int x = 0; x < 9; x++){
            if(y == available_numbers[x]){ 
                std::cout << y << " "; 
                available_sorted.push_back(y); 
                continue;
            }
        } 
    } endline;

    std::cout << "Missing: ";

    // Binary search for any number between 1-9 if not found store it as missing
    for(int y = 1; y <= 9; y++){
        if(!std::binary_search(available_sorted.begin(), available_sorted.end(), y)){
            std::cout << y << " ";
            missing_numbers.push_back(y);
        };
    } endline; endline;

    return missing_numbers;

}

// Check which column has least missing numbers, return the column number
void compare_columns(Sudoku &sudoku){}
// Check which row has least missing numbers, return the row number
void compare_rows(Sudoku &sudoku){}

// Make puzzle for faster copy paste
// Can take user input or hardcode puzzle key here
void make_puzzle(){
    std::string user_input;
    //std::cin >> user_input;

    // Hard
    user_input =
    "904670301257800060600509000070010092000008000429700010032050940190000573740006020";

    // Easy
    user_input =
    "400307600003002800028510704100823900000750128004009000602048351030070400009000280";

    std::cout << "array<array<int, 9>, 9> puzzle = {{" << std::endl;
    for(size_t x = 0; x < user_input.size(); x++){
        
        if(x == 0 || x % 9 == 0){ std::cout << "{ ";}
        std::cout  << user_input[x] << ", ";
        if((x+1) % 9 == 0){ std::cout << "},"; endline;}
    }
    std::cout << "}};" << std::endl;
}


/*

so theres 9 zones 
grid[0][0] grid[0][1] grid[0][2]    grid[0][3] grid[0][4] grid[0][5]    grid[0][6] grid[0][7] grid[0][8]
grid[1][0] grid[1][1] grid[1][2]    grid[1][3] grid[1][4] grid[1][5]    grid[1][6] grid[1][7] grid[1][8]
grid[2][0] grid[2][1] grid[2][2]    grid[2][3] grid[2][4] grid[2][5]    grid[2][6] grid[2][7] grid[2][8]

grid[3][0] grid[3][1] grid[3][2]  etc..
grid[4][0] grid[4][1] grid[4][2]  
grid[5][0] grid[5][1] grid[5][2]

grid[6][0] grid[6][1] grid[6][2]  etc..
grid[7][0] grid[7][1] grid[7][2]  
grid[8][0] grid[8][1] grid[8][2]
*/
#pragma once

#include "config.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;

class Sudoku{
    private:

    public:

        void run(){

        };

        std::array<std::array<int, 9>, 9> modern_p;

        int puzzle[9][9] =
        {
            { 9, 0, 4, 6, 7, 0, 3, 0, 1, },
            { 2, 5, 7, 8, 0, 0, 0, 6, 0, },
            { 6, 0, 0, 5, 0, 9, 0, 0, 0, },
            { 0, 7, 0, 0, 1, 0, 0, 9, 2, },
            { 0, 0, 0, 0, 0, 8, 0, 0, 0, },
            { 4, 2, 9, 7, 0, 0, 0, 1, 0, },
            { 0, 3, 2, 0, 5, 0, 9, 4, 0, },
            { 1, 9, 0, 0, 0, 0, 5, 7, 3, },
            { 7, 4, 0, 0, 0, 6, 0, 2, 0, },
        };

        int puzzle_size=(9*9);
};

// Position on grid (x, y)
struct Grid{
    int x;
    int y;
};

// Store current puzzle into provided vector
void puzzle_to_vector(Sudoku &sudoku, vector<int> &numbers){
    // Interestingly due to how arrays stored this will loop through
    for(int x = 0; x < (sudoku.puzzle_size); x++){
        numbers.push_back(sudoku.puzzle[0][x]);
    }
}
// Provide Column-y and Row-x to update puzzle with a number
void add_number(Sudoku &sudoku, int y, int x, int number){
    sudoku.puzzle[y][x] = number;
}

// Finds missing numbers from any 'available numbers' input and returns a vector missing numbers
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
    } endline;

    return missing_numbers;

}

// Check which column as least missing numbers, return the column number
void compare_columns(Sudoku &sudoku);
// Check which row as least missing numbers, return the row number
void compare_rows(Sudoku &sudoku);

// Make puzzle for faster copy paste, input string of numbers, can convert later
void make_puzzle(){
    std::string user_input;
    //std::cin >> user_input;
    // Can take user input or hardcode puzzle key here
    user_input =
    "904670301257800060600509000070010092000008000429700010032050940190000573740006020";

    std::cout << "int puzzle[9][9] =" << std::endl;
    std::cout << "{" << std::endl;
    for(int x = 0; x < user_input.size(); x++){
        
        if(x == 0 || x % 9 == 0){ std::cout << "{ ";}
        std::cout  << user_input[x] << ", ";
        if((x+1) % 9 == 0){ std::cout << "},"; endline;}
    }
    std::cout << "};" << std::endl;
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
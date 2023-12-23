#pragma once

#include "config.hpp"
#include <iostream>
#include <vector>
using std::vector;

class Sudoku{
    private:

    public:

        void run(){

        };

        int puzzle[9][9] = 
        {
            {9, 0, 4, 6, 7, 0, 3, 0, 1},
            {2, 5, 7, 8, 0, 0, 0, 6, 0},
            {6, 0, 0, 5, 0, 9, 0, 0, 0},
            {0, 7, 0, 0, 1, 0, 0, 9, 2},
            {0, 0, 0, 0, 0, 8, 0, 0, 0},
            {4, 2, 9, 7, 0, 0, 0, 1, 0},
            {0, 3, 2, 0, 5, 0, 9, 4, 0},
            {1, 9, 0, 0, 0, 0, 5, 7, 3},
            {7, 4, 0, 0, 0, 6, 0, 2, 0},
        };
};

struct Grid{
    int x;
    int y;
};

void puzzle_to_vector(Sudoku &sudoku, vector<int> &numbers){
    // self note later change to 2D loop
    for(int x = 0; x < (9*9); x++){
        numbers.push_back(sudoku.puzzle[0][x]);
    }
}

vector<int> get_missing_zone_numbers(Sudoku &sudoku, vector<int> &zone_numbers, int zone){
    vector<int> available_numbers;
    vector<int> missing_numbers;
    std::cout << "Available: ";
    for(int x = 0; x < (int)zone_numbers.size(); x++){
        if(zone_numbers[x] != 0){ std::cout << zone_numbers[x] << " "; available_numbers.push_back(x); }
    } newline;



    return missing_numbers;
}

// Provide Column-y and Row-x to update puzzle with a number
void add_number(Sudoku &sudoku, int y, int x, int number){
    sudoku.puzzle[y][x] = number;
}

/*

case zone 0: grid y < 3 && grid x < 3
case zone 1: grid y < 3 && (grid x < 6 && grid x >= 3)
case zone 2: grid y < 3 && (grid x < 6 && grid x >= 3)

case zone 3: (grid y >= 3 && grid y < 6) && grid x < 3
case zone 4: (grid y >= 3 && grid y < 6) && (grid x < 6 && grid x >= 3)

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
#pragma once

#include <vector>

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

void puzzle_to_vector(Sudoku &sudoku, std::vector<int> &numbers){
    // self note later change to 2D loop
    for(int x = 0; x < 9; x++){
        numbers.push_back(sudoku.puzzle[0][x]);
    }
}

// Get the relevant zone of the selected cell, returns -1 if no zone hit
int get_zone(int y, int x){

    // Zone 0-2
    if(y < 3 && x < 3){ return 0; }
    else if(y < 3 && (x < 6 && x >= 3)){ return 1; }
    else if(y < 3 && (x < 9 && x >= 6)){ return 2; }

    // Zone 3-5
    else if((y >= 3 && y < 6) && x < 3){ return 3; }
    else if((y >= 3 && y < 6) && (x < 6 && x >= 3)){ return 4; }
    else if((y >= 3 && y < 6) && (x < 9 && x >= 6)){ return 5; }

    // Zone 6-8
    else if((y >= 6 && y < 9) && x < 3){ return 6; }
    else if((y >= 6 && y < 9) && (x < 6 && x >= 3)){ return 7; }
    else if((y >= 6 && y < 9) && (x < 9 && x >= 6)){ return 8; }

    else { return -1; }
}

// Takes zone and returns that zones numbers to a vector
void store_zone(Sudoku &sudoku, std::vector<int> &zone_numbers, int zone){
    switch (zone)
    {
        // Zone 0-2
        case 0:{
            for(int y = 0; y < 3; y++){
                for(int x = 0; x < 3; x++){
                    zone_numbers.push_back(sudoku.puzzle[y][x]);
                }
            }
            break;
        }
        case 1:{
            for(int y = 0; y < 3; y++){
                for(int x = 3; x < 6; x++){
                    zone_numbers.push_back(sudoku.puzzle[y][x]);
                }
            }
            break;
        }
        case 2:{
            for(int y = 0; y < 3; y++){
                for(int x = 6; x < 9; x++){
                    zone_numbers.push_back(sudoku.puzzle[y][x]);
                }
            }
            break;
        }

        // Zone 3-5
        case 3:{
            for(int y = 3; y < 6; y++){
                for(int x = 0; x < 3; x++){
                    zone_numbers.push_back(sudoku.puzzle[y][x]);
                }
            }
            break;
        }
        case 4:{
            for(int y = 3; y < 6; y++){
                for(int x = 3; x < 6; x++){
                    zone_numbers.push_back(sudoku.puzzle[y][x]);
                }
            }
            break;
        }
        case 5:{
            for(int y = 3; y < 6; y++){
                for(int x = 6; x < 9; x++){
                    zone_numbers.push_back(sudoku.puzzle[y][x]);
                }
            }
            break;
        }

        // Zone 6-8
        case 6:{
            for(int y = 6; y < 9; y++){
                for(int x = 0; x < 3; x++){
                    zone_numbers.push_back(sudoku.puzzle[y][x]);
                }
            }
            break;
        }
        case 7:{
            for(int y = 6; y < 9; y++){
                for(int x = 3; x < 6; x++){
                    zone_numbers.push_back(sudoku.puzzle[y][x]);
                }
            }
            break;
        }
        case 8:{
            for(int y = 6; y < 9; y++){
                for(int x = 6; x < 9; x++){
                    zone_numbers.push_back(sudoku.puzzle[y][x]);
                }
            }
            break;
        }

        default:{
            std::cout << "Zone not found" << std::endl;
            break;
        }
    }
}

void push_zone_number(Sudoku &sudoku, std::vector<int> &zone_numbers){

    for(int y = 0; y < 3; y++){
        for(int x = 0; x < 3; x++){
            zone_numbers.push_back(sudoku.puzzle[y][x]);
        }
    }
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
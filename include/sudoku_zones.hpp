#pragma once

#include "sudoku.hpp"
#include <vector>
#include <iostream>

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

// Takes zone and store into provided vector array
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
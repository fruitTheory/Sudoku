#pragma once

#include "sudoku.hpp"
#include <vector>
#include <iostream>

// Get the relevant zone of selected cell, returns -1 if no zone hit
int get_zone(Grid &grid){

    int y = grid.y; int x = grid.x; 
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

// Takes zone and returns the zone cell numbers
std::vector<int> get_zone_numbers(Sudoku &sudoku, int zone){

    std::vector<int> zone_numbers;

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
            throw std::runtime_error("Zone input not found");
        }
    }

    return zone_numbers;

}

// Takes zone and returns zone cell positions
std::vector<std::pair<int, int>> get_zone_positions(Sudoku &sudoku, int zone){

    std::vector<pair<int, int>> zone_coords;
    std::pair<int, int> coord;

    switch (zone)
    {
        // Zone 0-2
        case 0:{
            for(int y = 0; y < 3; y++){
                for(int x = 0; x < 3; x++){
                    coord.first = y; coord.second = x;
                    zone_coords.push_back(coord);
                }
            }
            break;
        }
        case 1:{
            for(int y = 0; y < 3; y++){
                for(int x = 3; x < 6; x++){
                    coord.first = y; coord.second = x;
                    zone_coords.push_back(coord);
                }
            }
            break;
        }
        case 2:{
            for(int y = 0; y < 3; y++){
                for(int x = 6; x < 9; x++){
                    coord.first = y; coord.second = x;
                    zone_coords.push_back(coord);
                }
            }
            break;
        }

        // Zone 3-5
        case 3:{
            for(int y = 3; y < 6; y++){
                for(int x = 0; x < 3; x++){
                    coord.first = y; coord.second = x;
                    zone_coords.push_back(coord);
                }
            }
            break;
        }
        case 4:{
            for(int y = 3; y < 6; y++){
                for(int x = 3; x < 6; x++){
                    coord.first = y; coord.second = x;
                    zone_coords.push_back(coord);
                }
            }
            break;
        }
        case 5:{
            for(int y = 3; y < 6; y++){
                for(int x = 6; x < 9; x++){
                    coord.first = y; coord.second = x;
                    zone_coords.push_back(coord);
                }
            }
            break;
        }

        // Zone 6-8
        case 6:{
            for(int y = 6; y < 9; y++){
                for(int x = 0; x < 3; x++){
                    coord.first = y; coord.second = x;
                    zone_coords.push_back(coord);
                }
            }
            break;
        }
        case 7:{
            for(int y = 6; y < 9; y++){
                for(int x = 3; x < 6; x++){
                    coord.first = y; coord.second = x;
                    zone_coords.push_back(coord);
                }
            }
            break;
        }
        case 8:{
            for(int y = 6; y < 9; y++){
                for(int x = 6; x < 9; x++){
                    coord.first = y; coord.second = x;
                    zone_coords.push_back(coord);
                }
            }
            break;
        }

        default:{
            throw std::runtime_error("Zone input not found, coord related");
        }
    }

    return zone_coords;

}
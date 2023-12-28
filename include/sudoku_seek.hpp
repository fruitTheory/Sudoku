#pragma once

#include "sudoku.hpp"
#include "sudoku_utility.hpp"
#include "sudoku_zones.hpp"
#include <vector>
#include <utility>
using std::vector;
using std::pair;


void zone_seek(Sudoku &sudoku, Grid &grid){

    // std::cout << "Zone:" << std::endl;
    int zone = get_zone(grid);
    vector<int> zone_numbers = get_zone_numbers(sudoku, zone);
    vector<pair<int, int>> zone_positions = get_zone_positions(sudoku, zone);
    vector<int> zone_missing =get_missing_numbers(zone_numbers);
    print_zone_numbers(zone_numbers, zone);
    print_vector_pairs(zone_positions);
}


void column_seek(Sudoku &sudoku, Grid &grid, int column){

    std::cout << "Column:" << std::endl;
    vector<int> column_numbers = get_column_numbers(sudoku, column);
    vector<pair<int, int>> column_positions = get_column_positions(sudoku, column);
    vector<int> column_missing = get_missing_numbers(column_numbers);
    print_vector(column_numbers);
    print_vector_pairs(column_positions);

    // print_puzzle(sudoku);
    // solve(sudoku, column_missing, column_positions);
    // print_puzzle(sudoku);

}

void row_seek(Sudoku &sudoku, Grid &grid, int row){

    std::cout << "Row:" << std::endl;
    vector<int> row_numbers = get_row_numbers(sudoku, row);
    vector<pair<int, int>> row_positions = get_column_positions(sudoku, row);
    vector<int> row_missing = get_missing_numbers(row_numbers);
    print_vector(row_numbers);
    print_vector_pairs(row_positions);
    
}
#include "sudoku_seek.hpp"
#include "sudoku.hpp"
#include "sudoku_utility.hpp"
#include "sudoku_zones.hpp"
#include "config.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using std::vector;
using std::pair;


void zone_seek(int position_y, int position_x){

    // std::cout << "Zone:" << std::endl;

    int zone = get_zone(position_y, position_x);
    vector<int> zone_numbers = get_zone_numbers(zone);
    vector<pair<int, int>> zone_positions = get_zone_positions(zone);
    vector<int> zone_missing =get_missing_numbers(zone_numbers);

    print_zone_numbers(zone_numbers, zone);
    print_vector_pairs(zone_positions);
}


void row_seek(int row){

    std::cout << "Row:" << std::endl;

    vector<int> row_numbers = get_row_numbers(row);
    vector<pair<int, int>> row_positions = get_row_positions(row);
    vector<int> row_missing = get_missing_numbers(row_numbers);

    print_vector(row_numbers);

    // Run a compare on all missing numbers
    for(size_t y = 0; y < row_missing.size(); y++){
        for(int x = 0; x < 9; x++){
            if(row_numbers[x] == 0){
                std::cout << row_numbers[x] << " \n";
                cross_column_compare(row_positions[x].second, row_missing[y]);
            }
        }
    }

    // cross_zone_compare(row_positions[0].first, row_positions[0].second, row_missing[0]);

    print_vector(row_missing);
    
}

// Call from row seek, takes a rows column and compare with the compare_value
void cross_column_compare(int column, int compare_value){

    vector<int> column_numbers = get_column_numbers(column);
    vector<pair<int, int>> column_positions = get_column_positions(column);

    std::sort(column_numbers.begin(), column_numbers.end());

    if(std::binary_search(column_numbers.begin(), column_numbers.end(), compare_value)){
        std::cout << "Found: " << compare_value << std::endl;
    }
}

// Check zone with the compare_value
void cross_zone_compare(int position_y, int position_x, int compare_value){

    int zone = get_zone(position_y, position_x);
    vector<int> zone_numbers = get_zone_numbers(zone);
    vector<pair<int, int>> zone_positions = get_zone_positions(zone);
    vector<int> zone_missing =get_missing_numbers(zone_numbers);

    if(std::binary_search(zone_numbers.begin(), zone_numbers.end(), compare_value)){
        std::cout << "Found: " << compare_value << std::endl;
    }
}

// void column_seek(int column){

//     std::cout << "Column:" << std::endl;

//     vector<int> column_numbers = get_column_numbers(column);
//     vector<pair<int, int>> column_positions = get_column_positions(column);
//     vector<int> column_missing = get_missing_numbers(column_numbers);

//     print_vector(column_numbers);
//     print_vector_pairs(column_positions);
// }


// // Call from column seek, takes a columns rows and compare with the compare_value
// void cross_row_compare(int row, int compare_value){

//     vector<int> row_numbers = get_column_numbers(row);
//     vector<pair<int, int>> column_positions = get_column_positions(row);

//     std::sort(row_numbers.begin(), row_numbers.end());

//     // Find if missing value 
//     if(std::binary_search(row_numbers.begin(), row_numbers.end(), compare_value)){
//         std::cout << "Found: " << compare_value << std::endl;
//     }
// }

// This is a state, ideally each missing number is in a state of being or not being per cell
// When a number for sure cant be in a spot this should be stored
void check_deduction(){

}

// void num_check(int row, int column){

//     std::cout << "Row:" << std::endl;

//     vector<int> row_numbers = get_row_numbers(row);
//     vector<pair<int, int>> row_positions = get_row_positions(row);
//     vector<int> row_missing = get_missing_numbers(row_numbers);

//     std::cout << "Column:" << std::endl;

//     vector<int> column_numbers = get_column_numbers(column);
//     vector<pair<int, int>> column_positions = get_column_positions(column);
//     vector<int> column_missing = get_missing_numbers(column_numbers);

//     print_vector(row_numbers);

//     // Run a compare on all missing numbers
//     for(size_t x = 0; x < row_missing.size(); x++){
//         cross_column_compare(row_positions[0].second, row_missing[x]);
//         cross_row_compare(row_positions[0].first, row_missing[x]);
//         cross_zone_compare(row_positions[0].first, row_positions[0].second, row_missing[x]);
//     } endline;

//     print_vector(row_missing);
    
// }
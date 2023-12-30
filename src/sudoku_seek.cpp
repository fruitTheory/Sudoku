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


void get_row_hits(int row){

    std::cout << "Row:" << std::endl;

    vector<int> row_numbers = get_row_numbers(row);
    vector<pair<int, int>> row_positions = get_row_positions(row);
    vector<int> row_missing = get_missing_numbers(row_numbers);

    print_vector(row_numbers);
    
    vector<int> hit_values;

    // Run a compare on all missing numbers
    for(size_t y = 0; y < row_missing.size(); y++){
        for(int x = 0; x < 9; x++){
            if(row_numbers[x] == 0){
                // loop through each row, passing along each missing number to compare
                int cross_compare_value = cross_compare_columns(row_positions[x].second, row_missing[y], x);
                hit_values.push_back(cross_compare_value);
            } else { hit_values.push_back(0); }
        }
    }

    // Of the missing values hit values lists where each value hit for each column
    print_vector(hit_values);
    print_vector(row_missing);

    // return hit_values;

    array<vector<int>, 9> column_array_hits = {};

    // Array of 9 vectors each representing a rows column
    // Within those vectors are numbers that where found as a hit
    // A hit is a (missing number that exists in that row)

    // Note: size of test vector was 45, always should be divisable by 9

    for(size_t x = 0; x < hit_values.size(); x++){
        if(hit_values[x] != 0){
            int column = (x % 9); // get column number
            int hit_value = hit_values[x]; // get the value hit
            column_array_hits[column].push_back(hit_value); // push value to relevant columm
        }
    }

    std::cout << "Hit values per column:\n\n";
    for(int x = 0; x < 9; x++){
        print_vector(column_array_hits[x]);
    }
    
    // return column_array_hits;
    
}

// Call from row seek, takes a column(for current row) and compares against a compare_value, needs 1-9 iteration
int cross_compare_columns(int column, int compare_value, int iteration){

    vector<int> column_numbers = get_column_numbers(column);
    vector<pair<int, int>> column_positions = get_column_positions(column);

    std::sort(column_numbers.begin(), column_numbers.end());

    int column_hit;

    if(std::binary_search(column_numbers.begin(), column_numbers.end(), compare_value)){
        std::cout << "Found: " << compare_value << std::endl;
        column_hit = compare_value;
    } else { column_hit = 0; }


    return column_hit;
}

// Check zone with the compare_value
void cross_compare_zone(int position_y, int position_x, int compare_value){

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
// void cross_compare_rows(int row, int compare_value){

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
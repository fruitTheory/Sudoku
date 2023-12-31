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

    // return hit_values;


    // Call column_crosscheck(vector<int> hit_values)
    array<vector<int>, 9> column_array_hits = {};
    // A hit is a (missing number that exists in that row)
    // Will check columns that cross row cell for hits

    // Note: size of vector should always be divisable by 9
    for(size_t x = 0; x < hit_values.size(); x++){
        if(hit_values[x] != 0){
            int column = (x % 9); // get column number
            int hit_value = hit_values[x]; // get the value hit
            column_array_hits[column].push_back(hit_value); // push value to relevant columm
        }
    }
    
    // Prints the hit values
    // std::cout << "Hit values per column:\n\n";
    // for(int x = 0; x < 9; x++){
    //     print_vector(column_array_hits[x]);
    // }

    // return column_array_hits;


    // Call get_empty_cells(vector<int> row_numbers)
    // Returns which row cells are empty, may not be needed, just separate out
    vector<int> empty_rows;
    for(int x = 0; x < 9; x++){
        if(row_numbers[x] == 0) { empty_rows.push_back(x); }
    }


    // Call get_possible_values(vector<int> &missing_numbers, array<vector<int>, 9> hits)
    // Returns possible numbers for each cell - rename func to get possible or somtn ^
    solve_temp(row_missing, row_positions, column_array_hits);
    
}

void solve_temp(vector<int> &missing_numbers, vector<pair<int, int>> positions, array<vector<int>, 9> hits){

    // print_vector(missing_numbers);
    array<vector<int>, 9> possible;

    // Loop and add possibilites to vector, should be opposite of hits vector
    for(size_t y = 0; y < missing_numbers.size(); y++){
        int compare_value = missing_numbers[y];
        // std::cout << "compare value: " << compare_value << " \n";
        for(int x = 0; x < 9; x++){
            int count = std::count(hits[x].begin(), hits[x].end(), compare_value);
            if(!count){ possible[x].push_back(compare_value); }
            // std::cout << count << " \n";
        }
    }

    for(int x = 0; x < 9; x++){
        //print_vector(hits[x]);
        print_vector(possible[x]);
    }
    // return possible;


    // Call solve(array<vector<int>, 9> possible)
    // std::cout << "test: " << possible[2][1]; endline;

    // If only one possible value, add to board
    for(int x = 0; x < 9; x++){
        if(possible[x].size() == 1){ 
            Sudoku::add_number(positions[x].first, positions[x].second, possible[x][0]); 
        }
    } print_puzzle();

    // int probability = 100/possible[2].size();
    // if(probability == 100){ 
    //     Sudoku::add_number(positions[2].first, positions[2].second, possible[2][0]); 
    // }
}

// Call from row seek, takes a column(for current row) and compares against a compare_value, needs 1-9 iteration
int cross_compare_columns(int column, int compare_value, int iteration){

    vector<int> column_numbers = get_column_numbers(column);
    vector<pair<int, int>> column_positions = get_column_positions(column);

    std::sort(column_numbers.begin(), column_numbers.end());

    int column_hit;

    if(std::binary_search(column_numbers.begin(), column_numbers.end(), compare_value)){
        // std::cout << "Found: " << compare_value << std::endl;
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
// void check_deduction(){

// }

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
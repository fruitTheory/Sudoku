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
    int zone = get_zone(position_y, position_x);
    vector<int> zone_numbers = get_zone_numbers(zone);
    vector<pair<int, int>> zone_positions = get_zone_positions(zone);
    vector<int> zone_missing = get_missing_numbers(zone_numbers);
}

void get_row_hits(int row){

    /*
        -------------Row Data----------------
    */

    // std::cout << "Row:" << std::endl;

    vector<int> row_numbers = get_row_numbers(row);
    vector<pair<int, int>> row_positions = get_row_positions(row);
    vector<int> row_missing = get_missing_numbers(row_numbers);

    // print_vector(row_numbers);
    
    vector<int> hit_values;

    // Run a compare on all missing numbers
    for(size_t y = 0; y < row_missing.size(); y++){
        for(int x = 0; x < 9; x++){
            if(row_numbers[x] == 0){
                // loop through each row, passing along each missing number to compare
                int cross_compare_value = cross_compare_columns(row_positions[x].second, row_missing[y]);
                hit_values.push_back(cross_compare_value);
            } else { hit_values.push_back(0); }
        }
    }

    // return hit_values;


    /*
        -------------Column Hits----------------
    */

    array<vector<int>, 9> global_array_hits;

    // Call column_crosscheck(vector<int> hit_values)
    array<vector<int>, 9> column_array_hits;
    // A hit is a (missing number that exists in that row)
    // Will check columns that cross row cell for hits

    // Note: size of vector should always be divisable by 9
    for(size_t x = 0; x < hit_values.size(); x++){
        if(hit_values[x] != 0){
            int column = (x % 9); // get column(cell) number
            int hit_value = hit_values[x]; // get the value hit
            column_array_hits[column].push_back(hit_value); // push value to relevant columm
            global_array_hits[column].push_back(hit_value); // push value to relevant columm
        }
    }

    // return column_array_hits;

    /*
        -------------Zones----------------
    */

    // store each cells zone in an array
    array<int, 9> zones;

    // Get zone id's for each rows cell
    for(int x = 0; x < 9; x++){
        int zone = get_zone(row_positions[x].first, row_positions[x].second);
        zones[x] = (zone);
    }


    // Store vectors of zone numbers in array
    array<vector<int>, 9> zone_array_numbers;

    // Get zone numbers related to each rows cell
    for(int x = 0; x < 9; x++){
        vector<int> zone_numbers = get_zone_numbers(zones[x]);
        zone_array_numbers[x] = (zone_numbers);
    }

    // Store vectors of zone hits, which values already exist relative to position
    vector<int> zone_hit_values;

    // Filter zone number data - return vectors clashing numbers
    for(size_t y = 0; y < row_missing.size(); y++){
        for(int x = 0; x < 9; x++){
            int cross_compare_value = cross_compare_zone(zone_array_numbers[x], row_missing[y]);
            zone_hit_values.push_back(cross_compare_value);
        }
    }

    // Store the hits of each array into relevant column
    array<vector<int>, 9> zone_array_hits;

    // Pushing missing numbers to relevant global column(cell)
    for(size_t x = 0; x < zone_hit_values.size(); x++){
        if(zone_hit_values[x] != 0){
            int column = (x % 9); // get column(cell) number
            int hit_value = zone_hit_values[x]; // get the value hit
            zone_array_hits[column].push_back(hit_value); // push value to relevant columm
            if(std::find(global_array_hits[column].begin(), // check for duplicates
            global_array_hits[column].end(), hit_value) == global_array_hits[column].end()){
            global_array_hits[column].push_back(hit_value); } // push value to relevant columm
        }
    }

    // Prints the hit values
    // std::cout << "Hit values per column global:\n\n";
    // for(int x = 0; x < 9; x++){
    //     print_vector(global_array_hits[x]);
    // }

    // print_vector_pairs(row_positions);
    // print_vector(row_missing);

    // for(int x = 0; x < 9; x++){
        // print_vector(zone_array_numbers[x]);
        // print_vector(column_array_hits[x]);
        // print_vector(zone_array_hits[x]);
    // }

    /*
        -------------Empty----------------
    */

    // Call get_empty_cells(vector<int> row_numbers)
    // Returns which row cells are empty, may not be needed, just separate out
    vector<int> empty_rows;
    for(int x = 0; x < 9; x++){
        if(row_numbers[x] == 0) { empty_rows.push_back(x); }
    }

    // return empty_rows;


    /*
        -------------Solve----------------
    */

    // Call get_possible_values(vector<int> &missing_numbers, array<vector<int>, 9> hits)
    // Returns possible numbers for each cell - rename func to get possible or somtn ^
    solve_temp(row_missing, row_positions, global_array_hits);
    
}

int num = 0;
void solve_temp(vector<int> &missing_numbers, vector<pair<int, int>> positions, array<vector<int>, 9> hits){

    array<vector<int>, 9> possible;

    // Loop and add possibilites to grid array, should be opposite of hits vector
    for(size_t y = 0; y < missing_numbers.size(); y++){
        int compare_value = missing_numbers[y];
        // std::cout << "compare value: " << compare_value << " \n";
        for(int x = 0; x < 9; x++){
            int count = std::count(hits[x].begin(), hits[x].end(), compare_value);
            if(!count){ possible[x].push_back(compare_value); }
            // std::cout << count << " \n";
        }
    }

    // return possible;

    for(int x = 0; x < 9; x++){
        print_vector(possible[x]);
    }

    print_puzzle();

    // WHEN SOLVING NEED WHICH CELLS ARE ALREADY FILLED array_cell[x].second
    // So extras that equal size == 1 dont also get a number, then can iterate with updated board in main

    for(int x = 0; x < 9; x++){
        if(possible[x].size() == 1){ 
            Sudoku::add_number(positions[x].first, positions[x].second, possible[x][0]); 
            //std::cout << possible[x][0] << std::endl;
        }
    } 
    print_puzzle();

}

// Call from row seek, takes a column(for current row) and compares against a compare_value, needs 1-9 iteration
int cross_compare_columns(int column, int compare_value){

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
int cross_compare_zone(vector<int> zone_vector_numbers, int compare_value){

    // Necessary for binary search -c-, can use std::find for unsorted
    std::sort(zone_vector_numbers.begin(), zone_vector_numbers.end());

    int values_hit;

    if(std::binary_search(zone_vector_numbers.begin(), zone_vector_numbers.end(), compare_value)){
        // std::cout << "hit: " << compare_value << std::endl;
        values_hit = compare_value; 
    } else{
        // std::cout << "0" << std::endl; 
        values_hit = (0); 
    }

    return values_hit;
}
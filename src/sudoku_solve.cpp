#include "sudoku_solve.hpp"
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


// Basic solver that takes row as input
void row_algorithm(int row){

    // Keep row in arr bounds 0-8
    if(row > 8){ row %= 9; }

    /*
        -------------Row Data----------------
    */

    vector<int> row_numbers = get_row_numbers(row);
    vector<pair<int, int>> row_positions = get_row_positions(row);
    vector<int> row_missing = get_missing_numbers(row_numbers);

    vector<int> hit_values;

    // Run a compare on all missing numbers
    for(size_t y = 0; y < row_missing.size(); y++){
        for(int x = 0; x < 9; x++){
            if(row_numbers[x] == 0){
                // loop through each row, passing along each missing number to compare
                int cross_compare_value = cross_compare_columns(row_positions[x].second, row_missing[y]);
                // std::cout << "Missing: " << row_missing[y] << std::endl;
                hit_values.push_back(cross_compare_value);
            } else { hit_values.push_back(0); }
        }
    }

    /*
        -------------Column Hits----------------
    */

    array<vector<int>, 9> global_array_hits;

    // Note: size of vector should always be divisable by 9
    for(size_t x = 0; x < hit_values.size(); x++){
        if(hit_values[x] != 0){
            int column = (x % 9); // get column(cell) number
            int hit_value = hit_values[x]; // get the value hit
            global_array_hits[column].push_back(hit_value); // push value to relevant columm
        }
    }

    /*
        -------------Zone Hits----------------
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
            if(std::find(global_array_hits[column].begin(), // if no duplicates
            global_array_hits[column].end(), hit_value) == global_array_hits[column].end()){
            global_array_hits[column].push_back(hit_value); } // push value to relevant global columm
        }
    }


    solve_row(row_missing, row_positions, global_array_hits);
    
}

void solve_row(vector<int> &missing_numbers, vector<pair<int, int>> positions, array<vector<int>, 9> hits){

    array<vector<int>, 9> possible;

    int cycles = Sudoku::cycles;

    // Loop and add possibilites to grid array, should be opposite of hits vector
    for(size_t y = 0; y < missing_numbers.size(); y++){
        int compare_value = missing_numbers[y];
        for(int x = 0; x < 9; x++){
            int count = std::count(hits[x].begin(), hits[x].end(), compare_value);
            // If its not count that means its possible for that cell - push back
            if(!count){ possible[x].push_back(compare_value); }
        }
    }

    // Using cycles to get current row
    if(cycles > 8){ cycles %= 9; }

    // Clear cell vectors that already have a number in puzzle
    for(int x = 0; x < 9; x++){
        if(Sudoku::puzzle[cycles][x] != 0){
            possible[x].clear();
        }
    }

    // for(int x = 0; x < 9; x++){
    //     print_vector(possible[x]);
    // }

    std::cout << "Puzzle before: " << std::endl;
    print_puzzle();

    for(int x = 0; x < 9; x++){
        if(possible[x].size() == 1){ 
            Sudoku::add_number(positions[x].first, positions[x].second, possible[x][0]); 
            std::cout << "Cycle: " << Sudoku::cycles << std::endl;
            // break;
        }
    }

    std::cout << "Puzzle after: " << std::endl;
    print_puzzle();

}

// Check if puzzle is solved, will return 1 on solve and 0 if not
int is_solved(){

    int solved = 0;
    size_t puzzle_size = Sudoku::puzzle.size();
    puzzle_size *= puzzle_size;

    for(size_t x = 0; x < puzzle_size; x++){
        int value = Sudoku::puzzle[0][x];
        if(value == 0){
            solved = 0;
            break;
        } else { solved = 1; }
    }

    if(solved){
        std::cout << "Solved after: " << Sudoku::cycles << " iterations" << std::endl; endline;
    }

    return solved;
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
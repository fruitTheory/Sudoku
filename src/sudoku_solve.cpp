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
    vector<int> row_missing = get_missing_numbers(row_numbers);

    if(row_missing.size() > 0){
        
        vector<pair<int, int>> row_positions = get_row_positions(row);
        
        /*
            -------------Column Hits----------------
        */

        vector<int> column_hit_values = column_hits_per_cell(row_missing, row_numbers, row_positions);
        array<vector<int>, 9> column_array_hits = convert_column_hits(column_hit_values);

        /*
            -------------Zone Hits----------------
        */

        vector<int> zone_hit_values = zone_hits_per_cell(row_positions, row_missing);
        array<vector<int>, 9> zone_array_hits = convert_zone_hits(zone_hit_values);

        /*
            -------------Global Hits----------------
        */
        array<vector<int>, 9> global_array_hits = combine_hit_arrays(column_array_hits, zone_array_hits);

        solve_row(row_missing, row_positions, global_array_hits);

    }
    
}

void solve_row(vector<int> &missing_numbers, vector<pair<int, int>> &positions, array<vector<int>, 9> &hits){

    array<vector<int>, 9> possible = get_possible_numbers(missing_numbers, hits);

    // std::cout << "Puzzle before: " << std::endl;
    // print_puzzle();

    for(int x = 0; x < 9; x++){
        if(possible[x].size() == 1){ 
            Sudoku::add_number(positions[x].first, positions[x].second, possible[x][0]); 
        }
    }

    // std::cout << "Puzzle after: " << std::endl;
    // print_puzzle();

    int total = get_puzzle_total();

    // If the puzzle is same size as previous cycles(9) then use backtrace
    if(Sudoku::cycles % 9 == 0){
        
        if(Sudoku::total_size == total){
            std::cerr << "Row Algorithm Failed: " << std::endl;
            Sudoku::backtrace = 1;
        }

        Sudoku::total_size = total;
    }
}

// Compares value to vector returns true if exists in vector
bool compare_value_vec(vector<int> vec, int compare_value){
    for(auto num : vec){
        if(num == compare_value){
            return true;
        }
    }
    return false;
}

// Compares value to vector returns true if exists in vector
bool compare_value_vec_pair(vector<pair<int, int>> vec_pair, pair<int, int> compare_value){
    for(auto num : vec_pair){
        if(num == compare_value){
            return true;
        }
    }
    return false;
}

pair<int, int> find_empty(){

    pair<int, int> coords;
    int y{0}; int x{0};

    for(auto row: Sudoku::puzzle){
        for(int value: row){  
            if(Sudoku::puzzle[y][x] == 0){
                coords.first = y; coords.second = x;
                goto abort;
            }
            x = (x+1) % 9;
        } y++;
    }

    abort:
    return coords;
}

bool solve_backtrace(){
    Sudoku::cycles++;
    vector<int> possible = {1,2,3,4,5,6,7,8,9};
    pair<int, int> coords = find_empty();

    if(is_solved()){
        print_puzzle();
        return true;
    }

    for(int number: possible){
        int zone = get_zone(coords.first, coords.second);

        if(valid_check(coords.first, coords.second, number, zone)){
            Sudoku::puzzle[coords.first][coords.second] = number;
            if(solve_backtrace()){
                return true;
            }
            Sudoku::puzzle[coords.first][coords.second] = 0;
        }
    }

    return false;
}

bool valid_check(int row, int column, int compare_value, int zone){

    int is_valid = false;
    vector<int> zone_numbers = get_zone_numbers(zone);

    int row_check = cross_compare_row(row, compare_value);
    int column_check = cross_compare_columns(column, compare_value);
    int zone_check = cross_compare_zone(zone_numbers, compare_value);

    // std::cout << row_check << column_check << zone_check << std::endl;

    if(row_check == 0 && column_check == 0 && zone_check == 0){
        is_valid = true;
    }

    return is_valid;

}

// Check if puzzle is solved, will return 1 on solve and 0 if not
bool is_solved(){

    int solved = false;
    size_t puzzle_size = Sudoku::puzzle.size();
    puzzle_size *= puzzle_size;

    for(size_t x = 0; x < puzzle_size; x++){
        int value = Sudoku::puzzle[0][x];
        if(value == 0){
            solved = 0;
            break;
        } else { solved = true; }
    }

    if(solved){
        std::cout << "Solved after: " << Sudoku::cycles << " iterations" << std::endl; endline;
    }

    return solved;
}

int get_puzzle_total(){
    int total = 0;
    for( array arr : Sudoku::puzzle){
        for ( int num : arr){
            total += num;
        }
    }

    return total;
}

// Returns which missing values are hit for each cell of a row - based on column hits
vector<int> column_hits_per_cell(vector<int> &row_missing, vector<int> &row_numbers, vector<pair<int, int>> &row_positions){

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

    return hit_values;
}

// Returns an array of vectors that contain column hits for each cell within a row
array<vector<int>, 9> convert_column_hits(vector<int> &hit_values){

    array<vector<int>, 9> converted_row_hits;
    // Note: size of vector should always be divisable by 9
    for(size_t x = 0; x < hit_values.size(); x++){
        if(hit_values[x] != 0){
            int column = (x % 9); // get column(cell) number
            int hit_value = hit_values[x]; // get the value hit
            converted_row_hits[column].push_back(hit_value); // push value to relevant columm
        }
    }

    return converted_row_hits;
}

vector<int> zone_hits_per_cell(vector<pair<int, int>> &row_positions, vector<int> &row_missing){
    // For storing each cells zone id
    array<int, 9> zones;

    // Get zone id's and store as int
    for(int x = 0; x < 9; x++){
        int zone = get_zone(row_positions[x].first, row_positions[x].second);
        zones[x] = (zone);
    }

    // For storing vectors of zone numbers in array
    array<vector<int>, 9> zone_array_numbers;

    // Get zone numbers related to each cells zone id and store as vector
    for(int x = 0; x < 9; x++){
        vector<int> zone_numbers = get_zone_numbers(zones[x]);
        zone_array_numbers[x] = (zone_numbers);
    }

    // For storing vectors of zone hits, meaning which values already exist in a zone
    vector<int> zone_hit_values;

    // Filter zone number data - return vectors clashing numbers
    for(size_t y = 0; y < row_missing.size(); y++){
        for(int x = 0; x < 9; x++){
            int cross_compare_value = cross_compare_zone(zone_array_numbers[x], row_missing[y]);
            zone_hit_values.push_back(cross_compare_value);
        }
    }

    return zone_hit_values;
}

// Convert zone hits into an array of vectors for each cell
array<vector<int>, 9> convert_zone_hits(vector<int> &zone_hit_values){

    // Store the hits of each array into relevant column
    array<vector<int>, 9> zone_array_hits;

    // Pushing missing numbers to relevant global column(cell)
    for(size_t x = 0; x < zone_hit_values.size(); x++){
        if(zone_hit_values[x] != 0){
            int column = (x % 9); // get column(cell) number
            int hit_value = zone_hit_values[x]; // get the value hit
            zone_array_hits[column].push_back(hit_value); 
        }
    }

    return zone_array_hits;
}

array<vector<int>, 9> combine_hit_arrays(array<vector<int>, 9> &column_hit_array, array<vector<int>, 9> &zone_hit_array){

    array<vector<int>, 9> global_array_hits;

    // Combine vectors of hit numbers, sort and erase duplicates
    for(int x = 0; x < 9; x++){

        global_array_hits[x] = std::move(column_hit_array[x]);
        global_array_hits[x].insert(global_array_hits[x].end(), zone_hit_array[x].begin(), zone_hit_array[x].end());

        std::sort(global_array_hits[x].begin(), global_array_hits[x].end());
        auto duplicate = std::unique(global_array_hits[x].begin(), global_array_hits[x].end());
        global_array_hits[x].erase(duplicate, global_array_hits[x].end());

    }

    return global_array_hits;
}

array<vector<int>, 9> get_possible_numbers(vector<int> &missing_numbers, array<vector<int>, 9> &hits){

    array<vector<int>, 9> possible;

    // Loop and add possibilites to grid array, should be opposite of hits vector
    for(size_t y = 0; y < missing_numbers.size(); y++){
        int compare_value = missing_numbers[y];
        for(int x = 0; x < 9; x++){
            int count = std::count(hits[x].begin(), hits[x].end(), compare_value);
            // If its not count that means its possible for that cell - push back
            if(!count){ possible[x].push_back(compare_value); }
        }
    }

    int cycles = Sudoku::cycles;
    if(cycles > 8){ cycles %= 9; } // Using cycles to get current row

    // Clear cell vectors that already have a solved number
    for(int x = 0; x < 9; x++){
        if(Sudoku::puzzle[cycles][x] != 0){
            possible[x].clear();
        }
    }

    return possible;
}

// Takes a column(from current row) and compares against a compare_value - returns 0 if value doesnt conflict
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

// Takes a row and compares against a compare_value - returns 0 if value doesnt conflict
int cross_compare_row(int row, int compare_value){

    vector<int> row_numbers = get_row_numbers(row);
    vector<pair<int, int>> row_positions = get_row_positions(row);

    std::sort(row_numbers.begin(), row_numbers.end());

    int row_hit;

    if(std::binary_search(row_numbers.begin(), row_numbers.end(), compare_value)){
        // std::cout << "Found: " << compare_value << std::endl;
        row_hit = compare_value;
    } else { row_hit = 0; }


    return row_hit;
}

// Check zone with the compare_value - returns 0 if value doesnt conflict
int cross_compare_zone(vector<int> &zone_vector_numbers, int compare_value){

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
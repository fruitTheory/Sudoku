#include "sudoku.hpp"
#include "sudoku_utility.hpp"
#include "sudoku_zones.hpp"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using std::vector;
using std::pair;


void zone_seek(Grid &grid){

    // std::cout << "Zone:" << std::endl;


    int zone = get_zone(grid);
    vector<int> zone_numbers = get_zone_numbers(zone);
    vector<pair<int, int>> zone_positions = get_zone_positions(zone);
    vector<int> zone_missing =get_missing_numbers(zone_numbers);



    print_zone_numbers(zone_numbers, zone);
    print_vector_pairs(zone_positions);
}


void column_seek(int column){

    std::cout << "Column:" << std::endl;


    vector<int> column_numbers = get_column_numbers(column);
    vector<pair<int, int>> column_positions = get_column_positions(column);
    vector<int> column_missing = get_missing_numbers(column_numbers);


    print_vector(column_numbers);
    print_vector_pairs(column_positions);


}

void row_seek(int row){

    std::cout << "Row:" << std::endl;


    vector<int> row_numbers = get_row_numbers( row);
    vector<pair<int, int>> row_positions = get_row_positions(row);
    vector<int> row_missing = get_missing_numbers(row_numbers);

    print_vector(row_numbers);


    // int available_size = 0; 
    // // Thinking somehow get positions of non-zero numbers
    // for(size_t x = 0; x < row_numbers.size(); x++){
    //     if(row_numbers[x] != 0){
    //         ++available_size;
    //         std::cout << row_numbers[x] << " ";
    //     }
    // } endline;

    // Run a compare on all missing numbers
    for(size_t x = 0; x < row_missing.size(); x++){
        cross_column_compare(row_positions[2].second, row_missing[x]);
    }

    // print_vector(row_numbers);
    // print_vector_pairs(row_positions);
    // print_vector(row_missing);
    
}

// Compare a rows column with the compare_value - search crossed column for value
void cross_column_compare(int column, int compare_value){

    vector<int> column_numbers = get_column_numbers(column);
    vector<pair<int, int>> column_positions = get_column_positions(column);
    vector<int> column_missing = get_missing_numbers(column_numbers);
    std::sort(column_numbers.begin(), column_numbers.end());


    if(std::binary_search(column_numbers.begin(), column_numbers.end(), compare_value)){
        std::cout << "Found: " << compare_value << std::endl;
    }

    
}

// This is a state, ideally each missing number is in a state of being or not being per cell
// When a number for sure cant be in a spot this should be stored
void check_deduction(){

}

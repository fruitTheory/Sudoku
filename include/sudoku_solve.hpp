#pragma once

#include "sudoku.hpp"

void row_algorithm(int row);
int cross_compare_row(int row, int compare_value, array<array<int, 9>, 9> &puzzle);
int cross_compare_columns(int column, int compare_value, array<array<int, 9>, 9> &puzzle);
int cross_compare_zone(vector<int> &zone_vector_numbers, int compare_value);
int valid_check(int row, int column, int compare_value, vector<int> &zone_numbers, array<array<int, 9>, 9> &puzzle);

vector<int> column_hits_per_cell(vector<int> &row_missing, vector<int> &row_numbers, vector<pair<int, int>> &row_positions);
array<vector<int>, 9> convert_column_hits(vector<int> &hit_values);

vector<int> zone_hits_per_cell(vector<pair<int, int>> &row_positions, vector<int> &row_missing);
array<vector<int>, 9> convert_zone_hits(vector<int> &zone_hit_values);

array<vector<int>, 9> combine_hit_arrays(array<vector<int>, 9> &column_hit_array, array<vector<int>, 9> &zone_hit_array);

void solve_row(vector<int> &missing_numbers,  vector<pair<int, int>> &positions,  array<vector<int>, 9> &hits);
bool solve_backtrace();
int is_solved(array<array<int, 9>, 9> &puzzle);

int get_puzzle_total(array<array<int, 9>, 9> puzzle);
array<vector<int>, 9> get_possible_numbers(vector<int> &missing_numbers, array<vector<int>, 9> &hits);
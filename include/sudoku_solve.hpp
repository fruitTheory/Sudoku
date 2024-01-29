#pragma once

#include "sudoku.hpp"

void row_algorithm(int row);
int cross_compare_columns(int column, int compare_value);
int cross_compare_zone(vector<int> zone_vector_numbers, int compare_value);

void solve_row(vector<int> &missing_numbers,  vector<pair<int, int>> positions,  array<vector<int>, 9> hits);
int is_solved();
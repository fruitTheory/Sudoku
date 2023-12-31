#pragma once

#include "sudoku.hpp"

void zone_seek(int position_y, int position_x);
void get_row_hits(int row);

int cross_compare_columns(int column, int compare_value, int iteration);
void cross_compare_zone(int position_y, int position_x, int compare_value);

void solve_temp(vector<int> &missing_numbers,  vector<pair<int, int>> positions,  array<vector<int>, 9> hits);

// void column_seek(int column);
// void cross_compare_rows(int row, int compare_value);
// void num_check(int row, int column);
// void check_deduction();
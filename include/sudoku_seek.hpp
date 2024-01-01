#pragma once

#include "sudoku.hpp"

void zone_seek(int position_y, int position_x);
void get_row_hits(int row);

int cross_compare_columns(int column, int compare_value);
vector<int> cross_compare_zone(vector<int> zone_vector_numbers, int compare_value);

void solve_temp(vector<int> &missing_numbers,  vector<pair<int, int>> positions,  array<vector<int>, 9> hits);
#pragma once

#include "sudoku.hpp"

void zone_seek(int position_y, int position_x);
void column_seek(int column);
void row_seek(int row);

void cross_column_compare(int column, int compare_value);
void cross_row_compare(int row, int compare_value);
void cross_zone_compare(int position_y, int position_x, int compare_value);

// This is a state, ideally each missing number is in a state of being or not being per cell
// When a number for sure cant be in a spot this should be stored
void check_deduction();

void num_check(int row, int column);
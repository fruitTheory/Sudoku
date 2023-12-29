#pragma once

#include "sudoku.hpp"

void zone_seek(Grid &grid);

void column_seek(int column);

void row_seek(int row);

// Compare a rows column with the compare_value - search crossed column for value
void cross_column_compare(int column, int compare_value);

// This is a state, ideally each missing number is in a state of being or not being per cell
// When a number for sure cant be in a spot this should be stored
void check_deduction();

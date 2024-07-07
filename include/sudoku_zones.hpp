#pragma once

#include "sudoku.hpp"
#include <vector>

// Get the relevant zone of selected cell, returns -1 if no zone hit
int get_zone(int pos_y, int pos_x);

// Takes zone and returns a vector of current zone numbers
std::vector<int> get_zone_numbers(int zone);

// Takes zone and returns zone cell positions
std::vector<std::pair<int, int>> get_zone_positions(int zone);
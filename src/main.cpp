#include <cstdlib>
#include <iostream>
#include <vector>
#include "sudoku.hpp"
#include "sudoku_utility.hpp"
using namespace std;

int main(){

    puts("Hello World!");

    Sudoku sudoku;
    vector<int> numbers;
    Grid grid;
    grid.x = 0; grid.y = 4;

    print_puzzle_row(sudoku, 0);
    print_puzzle(sudoku);
    add_number(sudoku, grid.x, grid.y, 6);
    puzzle_to_vector(sudoku, numbers);
    print_puzzle(sudoku);
    print_vector(numbers);

    int zone = get_zone(grid.x, grid.y);
    std::cout << "Zone: " << zone << std::endl;


    return EXIT_SUCCESS;

}

/*
Were looking to have 1-9 in every row/column
Check the row and see which is 0 or missing number
Check the row and see what numbers are available, and also what are missing from 1-9
Check the box its in and then check/cycle the number in there

For each time it gets a solution print new Board to file(debug)

Easy Puzzle Thoughts

first row is missing 2, 5, 8
column 2 of first row cant be 2 because it already exists in the cross path
so check can it be 5, 8? in this case no it cant be 5 because that also exists in cross path
so it must be 8

BUT what if both 5 and 8 were possible, check the other missing spots cross path to see if its possible 
    there to elimate one of the choices
Lets try something more complex with multipe missing numbers
It again can be 2, 5, or 8 with many open spots on cross path again checking the both cross paths 
    contrain 2 so if all other cross paths contain 2

NOW contemplating if its a mix, some cross checks do contain 2 some dont


So far:
1. Cross check path if missing number from that row is in the crossed column -> elimate
2. if multiple numbers left, check the cross colums of the other missing number spots and
    if all of them comtain one of the missing numbers in cross then that will go in the current spot


Hard Puzzle Thoughts

Notice start with row with most numbers not missing

row 9 only missing 1 3 7
spot 1 can 1 or 3(after box checking) - not 7
spot 2 can 1 or 3 - not 7  
spot 3 can 1 or 7 - not 3 -- deduction makes spot 3 = 7

so far:
- Check row and columns for what each spot can or can not contain
- Then check associated box for same data
- Now row 9 spot 1 and 2 cant be easily found so..

If no solution possible check Next row with the most amount of available numbers

row 6 missing 1 2 4 6

spot 1 can be 2 or 6
spot 2 can be 1 4 or 6
spot 3 can be any
spot 4 can be any

spot 2 cant be 2
idea: check the last previous row, and compare missing sqaures
    if that previous row already contains a missing value and is not 
    able to be compared against empty spot

for example row 9 has a 2 4 and 6 already
and none of those are blocking the empty test row slots except 4





*/
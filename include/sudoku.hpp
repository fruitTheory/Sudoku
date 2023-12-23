#pragma once


class Sudoku{
    private:

    public:

        void run(){

        };

        int puzzle[9][9] = 
        {
            {9, 0, 4, 6, 7, 0, 3, 0, 1},
            {2, 5, 7, 8, 0, 0, 0, 6, 0},
            {6, 0, 0, 5, 0, 9, 0, 0, 0},
            {0, 7, 0, 0, 1, 0, 0, 9, 2},
            {0, 0, 0, 0, 0, 8, 0, 0, 0},
            {4, 2, 9, 7, 0, 0, 0, 1, 0},
            {0, 3, 2, 0, 5, 0, 9, 4, 0},
            {1, 9, 0, 0, 0, 0, 5, 7, 3},
            {7, 4, 0, 0, 0, 6, 0, 2, 0},
        };
};

void print_puzzle_row(Sudoku sudoku, int row){
        for(int x = 0; x < 9; x++){
        std::cout << sudoku.puzzle[row][x] << " ";
    } puts("\n");
}

void print_puzzle(Sudoku sudoku){
    for(int y = 0; y < 9; y++){
        for(int x = 0; x < 9; x++){
            std::cout << sudoku.puzzle[y][x] << " ";
        } puts("");
    } puts("");
}

void store_puzzle(Sudoku sudoku, std::vector<int> &numbers){
    for(int x = 0; x < 9; x++){
        numbers.push_back(sudoku.puzzle[0][x]);
    }
}
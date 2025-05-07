#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

const int SIZE = 9;

typedef vector<vector<int>> Grid;

struct SudokuState {
    Grid board;
    int heuristic;

    bool operator<(const SudokuState &other) const {
        return heuristic < other.heuristic;
    }
};

int calculate_conflicts(const Grid &grid) {
    int conflicts = 0;

    for (int i = 0; i < SIZE; ++i) {
        vector<int> row(10, 0), col(10, 0);
        for (int j = 0; j < SIZE; ++j) {
            if (grid[i][j] != 0) row[grid[i][j]]++;
            if (grid[j][i] != 0) col[grid[j][i]]++;
        }
        for (int k = 1; k <= 9; ++k) {
            if (row[k] > 1) conflicts += row[k] - 1;
            if (col[k] > 1) conflicts += col[k] - 1;
        }
    }

    for (int boxRow = 0; boxRow < SIZE; boxRow += 3) {
        for (int boxCol = 0; boxCol < SIZE; boxCol += 3) {
            vector<int> box(10, 0);
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    if (grid[boxRow + i][boxCol + j] != 0)
                        box[grid[boxRow + i][boxCol + j]]++;
            for (int k = 1; k <= 9; ++k)
                if (box[k] > 1) conflicts += box[k] - 1;
        }
    }

    return conflicts;
}

void fill_random(Grid &grid, const vector<vector<bool>> &fixed) {
    for (int row = 0; row < SIZE; ++row) {
        vector<bool> used(10, false);
        for (int col = 0; col < SIZE; ++col)
            if (grid[row][col] != 0)
                used[grid[row][col]] = true;

        vector<int> available;
        for (int val = 1; val <= 9; ++val)
            if (!used[val])
                available.push_back(val);

        random_shuffle(available.begin(), available.end());

        int idx = 0;
        for (int col = 0; col < SIZE; ++col)
            if (!fixed[row][col])
                grid[row][col] = available[idx++];
    }
}

void print_grid(const Grid &grid) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j)
            cout << grid[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    srand(time(0));

    Grid initial = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    vector<vector<bool>> fixed(SIZE, vector<bool>(SIZE, false));
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (initial[i][j] != 0)
                fixed[i][j] = true;

    Grid current = initial;
    fill_random(current, fixed);

    int best_h = calculate_conflicts(current);
    int iterations = 10000;

    while (iterations--) {
        SudokuState best_state = {current, best_h};

        for (int row = 0; row < SIZE; ++row) {
            for (int i = 0; i < SIZE; ++i) {
                for (int j = i + 1; j < SIZE; ++j) {
                    if (!fixed[row][i] && !fixed[row][j]) {
                        swap(current[row][i], current[row][j]);
                        int h = calculate_conflicts(current);
                        if (h < best_state.heuristic)
                            best_state = {current, h};
                        swap(current[row][i], current[row][j]); // revert
                    }
                }
            }
        }

        if (best_state.heuristic < best_h) {
            current = best_state.board;
            best_h = best_state.heuristic;
        } else break;
    }

    cout << "\nFinal Sudoku (Heuristic = " << best_h << "):\n";
    print_grid(current);

    return 0;
}

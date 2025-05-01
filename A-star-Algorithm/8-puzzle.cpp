#include <bits/stdc++.h>
using namespace std;

class PuzzleState {
public:
    vector<vector<int>> board;
    int emptyRow, emptyCol;
    string boardString;
    int moves;
    int heuristic;
    PuzzleState* parent; // Pointer to parent state (needed for path reconstruction)
    PuzzleState(vector<vector<int>> b, int m = 0, PuzzleState* p = nullptr) {
        board = b;
        moves = m;
        parent = p;
        boardString = "";
        
        // Find empty tile and create board string
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    emptyRow = i;
                    emptyCol = j;
                }
                boardString += to_string(board[i][j]);
            }
        }
    }
    
    void calculateHeuristic(vector<vector<int>>& goalState) {
        heuristic = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int val = board[i][j];
                if (val != 0) { 
                    for (int gi = 0; gi < 3; gi++) {
                        for (int gj = 0; gj < 3; gj++) {
                            if (goalState[gi][gj] == val) {
                                heuristic += abs(i - gi) + abs(j - gj);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    
    bool isGoal(const vector<vector<int>>& goalState) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != goalState[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    vector<PuzzleState*> getNextStates() {
        vector<PuzzleState*> nextStates;
        const int dr[] = {-1, 1, 0, 0};
        const int dc[] = {0, 0, -1, 1};
        for (int i = 0; i < 4; i++) {
            int newRow = emptyRow + dr[i];
            int newCol = emptyCol + dc[i];
            if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
                vector<vector<int>> newBoard = board;
                swap(newBoard[emptyRow][emptyCol], newBoard[newRow][newCol]);
                nextStates.push_back(new PuzzleState(newBoard, moves + 1, this));
            }
        }
        return nextStates;
    }
    void printBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) cout << "  ";
                else cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
};

vector<PuzzleState*> solvePuzzle(vector<vector<int>> start, vector<vector<int>> goal) {
    // to choose less heuristic value from 2 values
    auto compare = [](PuzzleState* a, PuzzleState* b) {
        return (a->moves + a->heuristic) > (b->moves + b->heuristic);
    };
    // priority queue set the top as the less heuristic value
    priority_queue<PuzzleState*, vector<PuzzleState*>, decltype(compare)> openList(compare);
    // store already visited 
    unordered_set<string> closedList;
    PuzzleState* initial = new PuzzleState(start);
    initial->calculateHeuristic(goal);
    openList.push(initial);
    while (!openList.empty()) {
        PuzzleState* current = openList.top();
        openList.pop();
        // already found
        if (closedList.find(current->boardString) != closedList.end()) {
            delete current;
            continue;
        }
        // if goal found
        if (current->isGoal(goal)) {
            vector<PuzzleState*> path;
            PuzzleState* temp = current;
            while (temp != nullptr) {
                path.push_back(temp);
                temp = temp->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }
        // try calculating values of all combinations and storing them in pq
        closedList.insert(current->boardString);
        vector<PuzzleState*> nextStates = current->getNextStates();
        for (auto next : nextStates) {
            if (closedList.find(next->boardString) != closedList.end()) {
                delete next;
                continue;
            }
            next->calculateHeuristic(goal);
            openList.push(next);
        }
    }
    return {};
}

int main() {
    vector<vector<int>> initialState(3, vector<int>(3));
    cout << "Enter initial state (3x3 grid, use 0 for empty space):" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> initialState[i][j];
        }
    }
    vector<vector<int>> goalState(3, vector<int>(3));
    cout << "Enter goal state (3x3 grid, use 0 for empty space):" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> goalState[i][j];
        }
    }
    cout << "\nSolving puzzle...\n" << endl;
    vector<PuzzleState*> solution = solvePuzzle(initialState, goalState);
    
    if (solution.empty()) {
        cout << "No solution found!" << endl;
    }
    else {
        cout << "Solution found in " << solution.size() - 1 << " moves!" << endl << endl;
        for (int i = 0; i < solution.size(); i++) {
            cout << "Step " << i << ":" << endl;
            solution[i]->printBoard();
            cout << endl;
        }
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int ROOM_SIZE;

struct Object {
    int width, height;
    string name;
};

struct State {
    vector<vector<char>> room;
    int obj_index;
    int cost, heuristic;

    bool operator>(const State &other) const {
        return (cost + heuristic) > (other.cost + other.heuristic);
    }
};

bool can_place(const vector<vector<char>> &room, int x, int y, const Object &obj) {
    if (x + obj.height > ROOM_SIZE || y + obj.width > ROOM_SIZE) return false;
    for (int i = x; i < x + obj.height; ++i)
        for (int j = y; j < y + obj.width; ++j)
            if (room[i][j] != '.') return false;
    return true;
}

void place_object(vector<vector<char>> &room, int x, int y, const Object &obj, char mark) {
    for (int i = x; i < x + obj.height; ++i)
        for (int j = y; j < y + obj.width; ++j)
            room[i][j] = mark;
}

int estimate_empty_space(const vector<vector<char>> &room) {
    int empty = 0;
    for (int i = 0; i < ROOM_SIZE; ++i)
        for (int j = 0; j < ROOM_SIZE; ++j)
            if (room[i][j] == '.') ++empty;
    return empty;
}

void print_room(const vector<vector<char>> &room) {
    for (auto &row : room) {
        for (char cell : row) cout << cell << ' ';
        cout << '\n';
    }
}

int main() {
    cout << "Enter room size (NxN): ";
    cin >> ROOM_SIZE;

    int rect_count, square_count;
    cout << "Enter number of rectangular objects: ";
    cin >> rect_count;
    cout << "Enter number of square objects: ";
    cin >> square_count;

    vector<Object> objects;

    for (int i = 0; i < rect_count; ++i) {
        int w, h;
        string name;
        cout << "Enter name, width and height for rectangle " << i + 1 << ": ";
        cin >> name >> w >> h;
        objects.push_back({w, h, name});
    }

    for (int i = 0; i < square_count; ++i) {
        int s;
        string name;
        cout << "Enter name and side for square " << i + 1 << ": ";
        cin >> name >> s;
        objects.push_back({s, s, name});
    }

    priority_queue<State, vector<State>, greater<State>> open;
    vector<vector<char>> empty_room(ROOM_SIZE, vector<char>(ROOM_SIZE, '.'));
    open.push({empty_room, 0, 0, 0});

    while (!open.empty()) {
        State current = open.top(); open.pop();

        if (current.obj_index == objects.size()) {
            cout << "\nFinal Room Layout:\n";
            print_room(current.room);
            return 0;
        }

        Object obj = objects[current.obj_index];

        for (int i = 0; i < ROOM_SIZE; ++i) {
            for (int j = 0; j < ROOM_SIZE; ++j) {
                if (can_place(current.room, i, j, obj)) {
                    vector<vector<char>> new_room = current.room;
                    place_object(new_room, i, j, obj, obj.name[0]);

                    int new_cost = current.cost + 1;
                    int new_heuristic = estimate_empty_space(new_room);
                    open.push({new_room, current.obj_index + 1, new_cost, new_heuristic});
                }
            }
        }
    }

    cout << "No arrangement found.\n";
    return 0;
}

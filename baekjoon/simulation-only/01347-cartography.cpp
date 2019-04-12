#include <iostream>
#include <vector>

using namespace std;

enum class Direction : int { UP = 0, RIGHT, DOWN, LEFT };

size_t width = 1;
int row = 0, col = 0;
vector<vector<bool>> maze{{true}};

vector<bool> make_line_vec() {
    vector<bool> line_vec;
    line_vec.resize(width, false);
    return line_vec;
}

void move_on() {
    if (row == -1) {
        // Negative row
        maze.insert(maze.begin(), make_line_vec());
        row = 0;
    } else if (maze.size() < static_cast<size_t>(row + 1)) {
        // Not enough row
        maze.resize(row + 1, make_line_vec());
    }
    if (col == -1) {
        // Negative col
        width++;
        for (auto& row_vec : maze) {
            row_vec.insert(row_vec.begin(), false);
        }
        col = 0;
    } else if (maze[row].size() < static_cast<size_t>(col + 1)) {
        // Not enough col
        if (width < static_cast<size_t>(col + 1)) {
            width = col + 1;
        }
        maze[row].resize(width, false);
    }
    maze[row][col] = true;
}

void print_maze() {
    for (const auto& row_vec : maze) {
        for (const auto cell : row_vec) {
            cout << (cell ? '.' : '#');
        }
        for (size_t i = row_vec.size(); i < width; i++) {
            cout << '#';
        }
        cout << '\n';
    }
}

int main() {
    // Get n
    int n;
    cin >> n;

    // Move on
    auto direction = Direction::DOWN;
    while (n > 0) {
        int c = cin.get();
        switch (c) {
        case 'F':
            switch (direction) {
            case Direction::UP:
                row--;
                break;
            case Direction::RIGHT:
                col++;
                break;
            case Direction::DOWN:
                row++;
                break;
            case Direction::LEFT:
                col--;
            }
            move_on();
            break;
        case 'L':
            direction = static_cast<Direction>((static_cast<int>(direction) + 3) % 4);
            break;
        case 'R':
            direction = static_cast<Direction>((static_cast<int>(direction) + 1) % 4);
            break;
        default:
            continue;
        }
        n--;
    }

    print_maze();

    return 0;
}

#include <array>
#include <cstdio>
#include <list>
#include <tuple>

using namespace std;

using Point = pair<int, int>;
using Rotation = pair<int, bool>;

constexpr int N_MAX = 100;
constexpr int L_MAX = 100;
constexpr array<pair<int, int>, 4> DIRECTIONS{{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};

enum Cell : int { EMPTY = 0, SNAKE = 1, APPLE = 2, WALL = 4 };

int n, k, l;
Cell area[N_MAX + 2][N_MAX + 2] = {(Cell)0};
list<Point> snake_cells;
Rotation rotations[L_MAX + 1];

int elapsed_sec = 0;
int cur_direct = 0;
int cur_rotation = 0;

void run_snake_game() {
    while (true) {
        const auto& cur_pos = snake_cells.front();
        if (elapsed_sec == rotations[cur_rotation].first) {
            bool clockwise = rotations[cur_rotation].second;
            if (clockwise) {
                cur_direct = (cur_direct + 1) % 4;
            } else {
                cur_direct = (cur_direct + 3) % 4;
            }
            cur_rotation++;
        }

        int next_row = cur_pos.first + DIRECTIONS[cur_direct].first;
        int next_col = cur_pos.second + DIRECTIONS[cur_direct].second;
        switch (area[next_row][next_col]) {
        case EMPTY:
            area[snake_cells.back().first][snake_cells.back().second] = EMPTY;
            snake_cells.pop_back();
            break;
        case APPLE:
            break;
        case SNAKE:
        case WALL:
            return;
        }
        area[next_row][next_col] = SNAKE;
        snake_cells.emplace_front(make_pair(next_row, next_col));

        elapsed_sec++;
    }
}

int main() {
    snake_cells.emplace_front(make_pair(1, 1));
    area[1][1] = SNAKE;

    scanf("%d%d", &n, &k);

    for (int i = 0; i <= n + 1; i++) {
        area[0][i] = WALL;
        area[n + 1][i] = WALL;
        area[i][0] = WALL;
        area[i][n + 1] = WALL;
    }

    for (int i = 0; i < k; i++) {
        int row, col;
        scanf("%d%d", &row, &col);
        area[row][col] = APPLE;
    }

    scanf("%d", &l);

    for (int i = 0; i < l; i++) {
        int rot_sec;
        char direct_char;
        scanf("%d %c", &rot_sec, &direct_char);
        rotations[i].first = rot_sec;
        rotations[i].second = direct_char == 'D';
    }
    rotations[l].first = -1;

    run_snake_game();
    elapsed_sec++;

    printf("%d\n", elapsed_sec);

    return 0;
}

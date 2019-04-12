#include <array>
#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

using Point = pair<int, int>;

constexpr array<pair<int, int>, 4> DIRECTIONS{{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

constexpr int MAX_N = 50;
constexpr int MAX_M = 50;

enum DirectionIndex : int {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
};

enum Place : int {
    DIRTY = 0,
    WALL = 1,
    CLEANED = 2,
};

int n;
int m;
Place area[MAX_N][MAX_M];
int cur_row;
int cur_col;
DirectionIndex cur_dir;
int cleaned_count = 0;

void start_cleaning() {
    while (true) {
        int next_row, next_col;
        bool moved = false;
        if (area[cur_row][cur_col] == DIRTY) {
            area[cur_row][cur_col] = CLEANED;
            cleaned_count++;
        }
        for (int i = 0; i < 4; i++) {
            cur_dir = (DirectionIndex)(((int)cur_dir + 3) % 4);
            next_row = cur_row + DIRECTIONS[cur_dir].first;
            next_col = cur_col + DIRECTIONS[cur_dir].second;
            if (area[next_row][next_col] == DIRTY) {
                cur_row = next_row;
                cur_col = next_col;
                moved = true;
                break;
            }
        }
        if (!moved) {
            auto back_dir = (DirectionIndex)(((int)cur_dir + 2) % 4);
            next_row = cur_row + DIRECTIONS[back_dir].first;
            next_col = cur_col + DIRECTIONS[back_dir].second;
            if (area[next_row][next_col] != WALL) {
                cur_row = next_row;
                cur_col = next_col;
            } else {
                break;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    scanf("%d%d%d", &cur_row, &cur_col, (int*)&cur_dir);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", (int*)&area[i][j]);
        }
    }
    start_cleaning();
    printf("%d\n", cleaned_count);
    return 0;
}

#include <array>
#include <cstdio>
#include <tuple>

using namespace std;

enum DiceIndex : int {
    TOP = 0,
    NORTH = 1,
    EAST = 2,
    WEST = 3,
    SOUTH = 4,
    BOTTOM = 5,
};

constexpr int N_MAX = 20;
constexpr int M_MAX = 20;
constexpr array<pair<int, int>, 4> DIRECTIONS{{{0, 1}, {0, -1}, {-1, 0}, {1, 0}}};

int n;
int m;
int k;
int area[N_MAX][M_MAX];
int cur_row;
int cur_col;
int dice[6] = {0};

bool roll_dice(int dir_num) {
    int next_row = cur_row + DIRECTIONS[dir_num - 1].first;
    int next_col = cur_col + DIRECTIONS[dir_num - 1].second;
    if (next_row < 0 || next_row >= n || next_col < 0 || next_col >= m) {
        return false;
    }
    DiceIndex side, opposite;
    switch (dir_num) {
    case 1:
        side = EAST;
        opposite = WEST;
        break;
    case 2:
        side = WEST;
        opposite = EAST;
        break;
    case 3:
        side = NORTH;
        opposite = SOUTH;
        break;
    default:
        side = SOUTH;
        opposite = NORTH;
    }
    if (area[next_row][next_col] == 0) {
        int orig_side_value = dice[side];
        dice[side] = dice[TOP];
        dice[TOP] = dice[opposite];
        dice[opposite] = dice[BOTTOM];
        dice[BOTTOM] = orig_side_value;
        area[next_row][next_col] = orig_side_value;
    } else {
        dice[side] = dice[TOP];
        dice[TOP] = dice[opposite];
        dice[opposite] = dice[BOTTOM];
        dice[BOTTOM] = area[next_row][next_col];
        area[next_row][next_col] = 0;
    }
    cur_row = next_row;
    cur_col = next_col;
    return true;
}

int main() {
    scanf("%d%d%d%d%d", &n, &m, &cur_row, &cur_col, &k);
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            scanf("%d", &area[row][col]);
        }
    }
    for (int i = 0; i < k; i++) {
        int direction_num;
        scanf("%d", &direction_num);
        if (roll_dice(direction_num)) {
            printf("%d\n", dice[0]);
        }
    }
    return 0;
}

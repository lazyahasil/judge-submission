// Solved by brute force not BFS
#include <array>
#include <iostream>
#include <tuple>

using namespace std;

using Cell = char;

constexpr int BIG_NUMBER = 100000;

array<pair<int, int>, 4> directions{{
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1},
}};

int n;
Cell** aqua;

int cur_row;
int cur_col;
long level = 2;
int experi = 0;

Cell** dists;

struct TargetFish {
    int row;
    int col;
    long dist;
};
TargetFish target;

long calculate_dist_cell(int row, int col) {
    long min = BIG_NUMBER;
    for (const auto& direction : directions) {
        int adj_row = row + direction.first;
        int adj_col = col + direction.second;
        if (adj_row < 0 || adj_row >= n || adj_col < 0 || adj_col >= n) {
            continue;
        }
        long adj_dist = dists[adj_row][adj_col];
        if (adj_dist >= 0 && adj_dist + 1 < min) {
            min = adj_dist + 1;
        }
    }
    if (min == BIG_NUMBER) {
        return -2;
    }
    return min;
}

void update_dists_and_target() {
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            long cell = aqua[i][j];
            if (cell > level) {
                dists[i][j] = -1;
            } else {
                dists[i][j] = -2;
            }
        }
    }

    dists[cur_row][cur_col] = 0;

    bool is_updated;
    do {
        is_updated = false;
        for (auto i = 0; i < n; i++) {
            for (auto j = 0; j < n; j++) {
                if (dists[i][j] == -2) {
                    long new_cell = calculate_dist_cell(i, j);
                    if (new_cell != -2) {
                        dists[i][j] = (Cell)new_cell;
                        is_updated = true;
                    }
                }
            }
        }
    } while (is_updated);

    target.row = target.col = BIG_NUMBER;
    target.dist = BIG_NUMBER;

    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            long dist = dists[i][j];
            long cell = aqua[i][j];
            if (dist > 0 && cell != 0 && cell != level) {
                if (target.dist > dist) {
                    target.row = i;
                    target.col = j;
                    target.dist = dist;
                } else if (target.dist == dist) {
                    if (i < target.row || (i == target.row && j < target.col)) {
                        target.row = i;
                        target.col = j;
                        target.dist = dist;
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d", &n);

    aqua = new Cell*[n];
    dists = new Cell*[n];
    for (auto i = 0; i < n; i++) {
        aqua[i] = new Cell[n];
        dists[i] = new Cell[n];
    }

    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            long cell;
            scanf("%ld", &cell);
            if (cell == 9L) {
                cur_row = i;
                cur_col = j;
                aqua[i][j] = 0;
            } else {
                aqua[i][j] = (Cell)cell;
            }
        }
    }

    int stage = 0;
    while (true) {
        update_dists_and_target();
        if (target.row == BIG_NUMBER) {
            break;
        }
        stage += target.dist;
        aqua[target.row][target.col] = 0;
        cur_row = target.row;
        cur_col = target.col;
        experi++;
        if (experi == level) {
            experi = 0;
            level++;
        }
    }

    printf("%d\n", stage);

    return 0;
}

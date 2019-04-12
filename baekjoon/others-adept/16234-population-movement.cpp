// Disjoint sets
#include <array>
#include <cstdio>
#include <cstdlib>
#include <tuple>

using namespace std;

using Point = pair<long, long>;

const array<Point, 2> DIRECTIONS{{{-1, 0}, {0, -1}}};

long n;
long union_min;
long union_max;
long** nations;
Point** djsets;

bool collasping_union(long row, long col, long leader_row, long leader_col) {
    while (true) {
        auto& djset = djsets[row][col];
        if (djset.first < 0) {
            break;
        }
        row = djset.first;
        col = djset.second;
        djset.first = leader_row;
        djset.second = leader_col;
    }
    if (row == leader_row && col == leader_col) {
        return false;
    }
    auto& root_djset = djsets[row][col];
    djsets[leader_row][leader_col].first += root_djset.first;
    djsets[leader_row][leader_col].second += root_djset.second;
    root_djset.first = leader_row;
    root_djset.second = leader_col;
    return true;
}

Point find_root(long row, long col) {
    while (true) {
        const auto& djset = djsets[row][col];
        if (djset.first < 0) {
            break;
        }
        row = djset.first;
        col = djset.second;
    }
    return make_pair(row, col);
}

bool join_nations(long a_row, long a_col, long b_row, long b_col) {
    tie(a_row, a_col) = find_root(a_row, a_col);
    return collasping_union(b_row, b_col, a_row, a_col);
}

int main() {
    scanf("%ld%ld%ld", &n, &union_min, &union_max);

    nations = new long*[n];
    djsets = new Point*[n];
    for (auto i = 0; i < n; i++) {
        nations[i] = new long[n];
        djsets[i] = new Point[n];
        for (auto j = 0; j < n; j++) {
            long nation;
            scanf("%ld", &nation);
            nations[i][j] = nation;
            djsets[i][j].first = -1;
            djsets[i][j].second = nation;
        }
    }

    int day_count = 0;

    while (true) {
        bool joined = false;
        for (auto i = 0; i < n; i++) {
            for (auto j = 0; j < n; j++) {
                for (const auto& direction : DIRECTIONS) {
                    long b_row = static_cast<long>(i);
                    long b_col = static_cast<long>(j);
                    long a_row = b_row + direction.first;
                    long a_col = b_col + direction.second;
                    if (a_row >= 0 && a_col >= 0) {
                        long popul_diff = abs(nations[a_row][a_col] - nations[i][j]);
                        if (popul_diff >= union_min && popul_diff <= union_max) {
                            if (join_nations(a_row, a_col, b_row, b_col)) {
                                joined = true;
                            }
                        }
                    }
                }
            }
        }
        if (!joined) {
            break;
        }

        bool moved = false;
        for (auto i = 0; i < n; i++) {
            for (auto j = 0; j < n; j++) {
                Point leader = find_root(i, j);
                const auto& leader_djset = djsets[leader.first][leader.second];
                long union_count = -1 * leader_djset.first;
                long union_popul = leader_djset.second;
                long new_popul = union_popul / union_count;
                if (nations[i][j] != new_popul) {
                    moved = true;
                }
                nations[i][j] = new_popul;
            }
        }
        if (!moved) {
            break;
        }

        for (auto i = 0; i < n; i++) {
            for (auto j = 0; j < n; j++) {
                auto& djset = djsets[i][j];
                djset.first = -1;
                djset.second = nations[i][j];
            }
        }

        day_count++;
    }

    printf("%d\n", day_count);

    return 0;
}

#include <array>
#include <cstdio>
#include <cstring>
#include <tuple>

using namespace std;

constexpr int N_MAX = 100;
constexpr array<pair<int, int>, 4> DIRECTIONS{{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

int n;
int threshold = 1;
int max_cell = 1;
int max_union_count = 0;
int area[N_MAX][N_MAX];
bool visit[N_MAX][N_MAX];

void dfs(int row, int col) {
    visit[row][col] = true;
    for (const auto& direction : DIRECTIONS) {
        int next_row = row + direction.first;
        int next_col = col + direction.second;
        if (next_row >= 0 && next_row < n && next_col >= 0 && next_col < n) {
            if (area[next_row][next_col] >= threshold && !visit[next_row][next_col]) {
                dfs(next_row, next_col);
            }
        }
    }
}

void run_all_cases() {
    while (threshold <= max_cell) {
        for (int row = 0; row < n; row++) {
            memset(visit[row], 0, n * sizeof(**visit));
        }
        int union_count = 0;
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (area[row][col] >= threshold && !visit[row][col]) {
                    dfs(row, col);
                    union_count++;
                }
            }
        }
        if (union_count > max_union_count) {
            max_union_count = union_count;
        }
        threshold++;
    }
}

int main() {
    scanf("%d", &n);

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            int cell;
            scanf("%d", &cell);
            if (cell > max_cell) {
                max_cell = cell;
            }
            area[row][col] = cell;
        }
    }

    run_all_cases();

    printf("%d\n", max_union_count);

    return 0;
}

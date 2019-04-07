#include <array>
#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

using Point = pair<int, int>;

constexpr array<pair<int, int>, 4> DIRECTIONS{{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

constexpr int MAX_N = 8;
constexpr int MAX_M = 8;

enum Place : int {
    EMPTY = 0,
    WALL = 1,
    VIRUS = 2,
    INFECTION = 3,
};

int n;
int m;
Place area[MAX_N + 2][MAX_M + 2];
bool flags[MAX_N + 2][MAX_M + 2];
vector<Point> viruses;
int empty_count = 0;
int min_infection = 100000000;

void spread_infection() {
    queue<Point> q;
    int infection = 0;

    for (int i = 1; i <= n; i++) {
        memset(flags[i] + 1, 0, m * sizeof(**flags));
    }

    for (const auto& virus : viruses) {
        q.emplace(virus);
    }

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();

        if (flags[cur.first][cur.second]) {
            continue;
        }
        flags[cur.first][cur.second] = true;

        if (area[cur.first][cur.second] == EMPTY) {
            area[cur.first][cur.second] = INFECTION;
            infection++;
        }

        for (const auto& direction : DIRECTIONS) {
            int next_row = cur.first + direction.first;
            int next_col = cur.second + direction.second;
            if (area[next_row][next_col] != WALL && !flags[next_row][next_col]) {
                q.emplace(make_pair(next_row, next_col));
            }
        }
    }

    if (infection < min_infection) {
        min_infection = infection;
    }
}

void clear_infection() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (area[i][j] == INFECTION) {
                area[i][j] = EMPTY;
            }
        }
    }
}

void brute_force(int r, int start_row, int start_col) {
    if (start_col > m) {
        start_row++;
        start_col = 1;
    }
    if (r == 3) {
        spread_infection();
        clear_infection();
        return;
    }

    for (int j = start_col; j <= m; j++) {
        if (area[start_row][j] == EMPTY) {
            area[start_row][j] = WALL;
            brute_force(r + 1, start_row, j + 1);
            area[start_row][j] = EMPTY;
        }
    }
    for (int i = start_row + 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (area[i][j] == EMPTY) {
                area[i][j] = WALL;
                brute_force(r + 1, i, j + 1);
                area[i][j] = EMPTY;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i <= m + 1; i++) {
        area[0][i] = WALL;
        area[n + 1][i] = WALL;
    }
    for (int i = 1; i <= n; i++) {
        area[i][0] = WALL;
        area[i][m + 1] = WALL;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            Place place;
            scanf("%d", (int*)&place);
            switch (place) {
            default:
                break;
            case EMPTY:
                empty_count++;
                break;
            case VIRUS:
                viruses.emplace_back(make_pair(i, j));
            }
            area[i][j] = place;
        }
    }

    brute_force(0, 1, 1);

    printf("%d\n", empty_count - min_infection - 3);

    return 0;
}

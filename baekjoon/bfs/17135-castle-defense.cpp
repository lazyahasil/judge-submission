// This can be solved by DFS (shorter implementation available)
#include <array>
#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>

using namespace std;

using Point = pair<int, int>;

constexpr array<pair<int, int>, 3> DIRECTIONS{{{-1, 0}, {0, -1}, {0, 1}}};
constexpr int N_MAX = 15;
constexpr int M_MAX = 15;

int n;
int m;
int d_max;
int area[N_MAX][M_MAX];  // 1 -> enemy, 2 -> body
int archers[3];
int max_kills = 0;

int stage;
queue<Point>* q1;
queue<Point>* q2;
bool visit[N_MAX][M_MAX];
Point targets[3];

void bfs(int archer_num) {
    int d = 1;
    auto& target = targets[archer_num];
    target.first = -1;
    target.second = -1;
    for (int i = 0; i < n; i++) {
        memset(visit[i], 0, m * sizeof(**visit));
    }
    q1->emplace(make_pair(n - stage, archers[archer_num]));

    while (true) {
        while (!q1->empty()) {
            auto point = q1->front();
            q1->pop();
            if (visit[point.first][point.second]) {
                continue;
            }
            visit[point.first][point.second] = true;
            if (area[point.first][point.second] == 1) {
                if (target.first == -1 || point.second < target.second) {
                    target = move(point);
                }
            }
            for (const auto& direction : DIRECTIONS) {
                int next_row = point.first + direction.first;
                int next_col = point.second + direction.second;
                if (next_row >= 0 && next_col >= 0 && next_col < m && !visit[next_row][next_col]) {
                    q2->emplace(make_pair(next_row, next_col));
                }
            }
        }
        if (q2->empty() || target.first != -1 || d >= d_max) {
            break;
        }
        swap(q1, q2);
        d++;
    }

    while (!q1->empty()) {
        q1->pop();
    }
    while (!q2->empty()) {
        q2->pop();
    }
}

void run_defense() {
    int kills = 0;
    stage = 1;

    while (stage <= n) {
        for (int i = 0; i < 3; i++) {
            bfs(i);
        }
        for (int i = 0; i < 3; i++) {
            const auto& target = targets[i];
            if (target.first != -1) {
                if (area[target.first][target.second] == 1) {
                    area[target.first][target.second] = 2;
                    kills++;
                }
            }
        }
        stage++;
    }
    if (kills > max_kills) {
        max_kills = kills;
    }

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (area[row][col] == 2) {
                area[row][col] = 1;
            }
        }
    }
}

void combination(int q, int r) {
    if (r == 0) {
        run_defense();
        return;
    }
    if (q < r) {
        return;
    }
    archers[r - 1] = q - 1;
    combination(q - 1, r - 1);
    combination(q - 1, r);
}

int main() {
    q1 = new queue<Point>();
    q2 = new queue<Point>();

    scanf("%d%d%d", &n, &m, &d_max);

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            scanf("%d", &area[row][col]);
        }
    }

    combination(m, 3);

    printf("%d\n", max_kills);

    return 0;
}

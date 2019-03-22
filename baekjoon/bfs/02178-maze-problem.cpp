#include <cstdio>
#include <queue>
#include <tuple>

using namespace std;

using Point = pair<int, int>;

constexpr array<pair<int, int>, 4> DIRECTIONS{{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

bool maze[100][100];
int n;
int m;
int count = 1;
queue<Point>* point_q1;
queue<Point>* point_q2;

int main() {
    point_q1 = new queue<Point>;
    point_q2 = new queue<Point>;

    scanf("%d%d", &n, &m);

    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < m; j++) {
            char maze_char;
            scanf(" %c", &maze_char);
            maze[i][j] = maze_char == '0';
        }
    }

    point_q1->emplace(make_pair(0, 0));

    while (true) {
        bool found = false;
        while (!point_q1->empty()) {
            const auto point = point_q1->front();
            point_q1->pop();
            if (maze[point.first][point.second]) {
                continue;
            }
            if (point.first == n - 1 && point.second == m - 1) {
                found = true;
                break;
            }
            maze[point.first][point.second] = true;
            for (const auto& direction : DIRECTIONS) {
                auto new_point
                    = make_pair(point.first + direction.first, point.second + direction.second);
                if (new_point.first >= 0 && new_point.first < n && new_point.second >= 0
                    && new_point.second < m) {
                    if (!maze[new_point.first][new_point.second]) {
                        point_q2->emplace(move(new_point));
                    }
                }
            }
        }
        if (found || point_q2->empty()) {
            break;
        }
        swap(point_q1, point_q2);
        count++;
    }

    printf("%d\n", count);

    return 0;
}

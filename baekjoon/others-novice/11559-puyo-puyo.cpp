#include <array>
#include <cstdio>
#include <cstring>
#include <tuple>
#include <vector>

using namespace std;

using Point = pair<int, int>;

constexpr int N = 12;
constexpr int M = 6;
constexpr array<pair<int, int>, 4> DIRECTIONS{{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}};

enum Cell : int { RED = 0, GREEN = 1, BLUE = 2, PURPLE = 3, YELLOW = 4, TOKILL = 9 };

array<vector<Cell>, M> board;  // (col-first, row-reversed)
vector<Point> chain;
bool visit[M][N] = {0};
int pangs = 0;

int dfs(int col, int revr, int count, Cell c) {
    visit[col][revr] = true;
    chain.emplace_back(make_pair(col, revr));
    for (const auto& direction : DIRECTIONS) {
        int next_col = col + direction.first;
        int next_revr = revr + direction.second;
        if (next_col >= 0 && next_col < M && next_revr >= 0 && next_revr < N) {
            if (!visit[next_col][next_revr] && next_revr < (int)board[next_col].size()) {
                if (board[next_col][next_revr] == c) {
                    count = dfs(next_col, next_revr, count + 1, c);
                }
            }
        }
    }
    return count;
}

void puyopyuo() {
    while (true) {
        bool topang = false;
        chain.clear();
        for (int col = 0; col < M; col++) {
            for (int revr = 0; revr < (int)board[col].size(); revr++) {
                if (!visit[col][revr]) {
                    chain.clear();
                    if (dfs(col, revr, 1, board[col][revr]) >= 4) {
                        topang = true;
                        for (const Point& point : chain) {
                            board[point.first][point.second] = TOKILL;
                        }
                    }
                }
            }
        }
        if (!topang) {
            break;
        }
        pangs++;
        for (auto& line : board) {
            int revr = 0;
            while (revr < (int)line.size()) {
                if (line[revr] == TOKILL) {
                    line.erase(line.begin() + revr);
                } else {
                    revr++;
                }
            }
        }
        for (int col = 0; col < M; col++) {
            memset(visit[col], 0, N * sizeof(**visit));
        }
    }
}

int main() {
    char buf[M + 1];

    for (int row = 0; row < N; row++) {
        scanf("%s", buf);
        for (int col = 0; col < M; col++) {
            Cell cell;
            switch (buf[col]) {
            default:
                continue;
            case 'R':
                cell = RED;
                break;
            case 'G':
                cell = GREEN;
                break;
            case 'B':
                cell = BLUE;
                break;
            case 'P':
                cell = PURPLE;
                break;
            case 'Y':
                cell = YELLOW;
            }
            if (board[col].empty()) {
                board[col].resize(N - row);
            }
            board[col][N - row - 1] = cell;
        }
    }

    puyopyuo();

    printf("%d\n", pangs);

    return 0;
}

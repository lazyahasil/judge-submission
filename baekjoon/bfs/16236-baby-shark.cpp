#include <array>
#include <cstdio>
#include <queue>
#include <tuple>

using namespace std;

using Point = pair<int, int>;

constexpr int BIG_NUMBER = 100000;
const array<pair<int, int>, 4> DIRECTIONS{{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

int n;
long** aqua;
bool** flags;
long level = 2;
queue<Point>* step_q1;
queue<Point>* step_q2;
int cur_row;
int cur_col;
long cur_dist;
int target_row;
int target_col;

void push_near_steps(int row, int col) {
    for (const auto& direction : DIRECTIONS) {
        int near_row = row + direction.first;
        int near_col = col + direction.second;
        if (near_row >= 0 && near_row < n && near_col >= 0 && near_col < n) {
            if (!flags[near_row][near_col]) {
                step_q2->emplace(make_pair(near_row, near_col));
            }
        }
    }
}

void run_bfs() {
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            if (aqua[i][j] > level) {
                flags[i][j] = true;
            } else {
                flags[i][j] = false;
            }
        }
    }

    cur_dist = 0;
    target_row = target_col = BIG_NUMBER;
    step_q1->emplace(make_pair(cur_row, cur_col));

    bool fish_found = false;
    while (true) {
        while (!step_q1->empty()) {
            auto step = step_q1->front();
            step_q1->pop();
            if (flags[step.first][step.second]) {
                continue;
            }
            flags[step.first][step.second] = true;
            long cur_step_value = aqua[step.first][step.second];
            if (fish_found) {
                if (cur_step_value != 0 && cur_step_value != level
                    && (step.first < target_row
                        || (step.first == target_row && step.second < target_col))) {
                    tie(target_row, target_col) = step;
                }
            } else {
                if (cur_step_value == 0 || cur_step_value == level) {
                    push_near_steps(step.first, step.second);
                } else {
                    fish_found = true;
                    tie(target_row, target_col) = step;
                }
            }
        }
        if (fish_found) {
            while (!step_q2->empty()) {
                step_q2->pop();
            }
            break;
        }
        if (step_q2->empty()) {
            break;
        }
        swap(step_q1, step_q2);
        cur_dist++;
    }
}

int main() {
    step_q1 = new queue<Point>;
    step_q2 = new queue<Point>;

    scanf("%d", &n);

    aqua = new long*[n];
    flags = new bool*[n];
    for (auto i = 0; i < n; i++) {
        aqua[i] = new long[n];
        flags[i] = new bool[n];
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
                aqua[i][j] = cell;
            }
        }
    }

    int stage = 0;
    int experi = 0;
    while (true) {
        run_bfs();
        if (target_row == BIG_NUMBER) {
            break;
        }
        stage += cur_dist;
        aqua[target_row][target_col] = 0;
        cur_row = target_row;
        cur_col = target_col;
        experi++;
        if (experi == level) {
            experi = 0;
            level++;
        }
    }

    printf("%d\n", stage);

    return 0;
}

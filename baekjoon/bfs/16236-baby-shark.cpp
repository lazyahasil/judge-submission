#include <array>
#include <cstdio>
#include <queue>
#include <tuple>

using namespace std;

constexpr int BIG_NUMBER = 100000;
const array<pair<int, int>, 4> DIRECTIONS{{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

int n;
long** aqua;
bool** flags;
long level = 2;
queue<pair<int, int>>* cur_step_q_ptr;
queue<pair<int, int>>* next_step_q_ptr;
int cur_row;
int cur_col;
long cur_dist;
int target_row;
int target_col;

void push_near_steps(queue<pair<int, int>>& q, int row, int col) {
    for (const auto& direction : DIRECTIONS) {
        int near_row = row + direction.first;
        int near_col = col + direction.second;
        if (near_row >= 0 && near_row < n && near_col >= 0 && near_col < n) {
            if (!flags[near_row][near_col]) {
                q.push(make_pair(near_row, near_col));
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
    flags[cur_row][cur_col] = true;
    push_near_steps(*cur_step_q_ptr, cur_row, cur_col);
    cur_dist = 1;
    target_row = target_col = BIG_NUMBER;

    bool fish_found = false;
    while (true) {
        while (!cur_step_q_ptr->empty()) {
            auto step = cur_step_q_ptr->front();
            cur_step_q_ptr->pop();
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
                    push_near_steps(*next_step_q_ptr, step.first, step.second);
                } else {
                    fish_found = true;
                    tie(target_row, target_col) = step;
                }
            }
        }
        if (fish_found) {
            while (!next_step_q_ptr->empty()) {
                next_step_q_ptr->pop();
            }
            break;
        }
        if (next_step_q_ptr->empty()) {
            break;
        }
        swap(cur_step_q_ptr, next_step_q_ptr);
        cur_dist++;
    }
}

int main() {
    cur_step_q_ptr = new queue<pair<int, int>>;
    next_step_q_ptr = new queue<pair<int, int>>;

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

#include <cstdio>

using namespace std;

constexpr int N_MAX = 20;

enum Direction : int { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };

int n;
int boards[6][N_MAX][N_MAX];
int max_block = 0;

void run_stage(int stage, Direction d) {
    const auto& prev_b = boards[stage - 1];
    auto& cur_b = boards[stage];
    int cur_pos;
    bool mergeable;

    switch (d) {
    case UP:
        for (int col = 0; col < n; col++) {
            cur_pos = -1;
            mergeable = false;
            for (int row = 0; row < n; row++) {
                if (prev_b[row][col] != 0) {
                    if (mergeable) {
                        if (prev_b[row][col] == cur_b[cur_pos][col]) {
                            cur_b[cur_pos][col] *= 2;
                            mergeable = false;
                            continue;
                        }
                    }
                    cur_b[++cur_pos][col] = prev_b[row][col];
                    mergeable = true;
                }
            }
            cur_pos++;
            while (cur_pos < n) {
                cur_b[cur_pos++][col] = 0;
            }
        }
        break;
    case RIGHT:
        for (int row = 0; row < n; row++) {
            cur_pos = n;
            mergeable = false;
            for (int col = n - 1; col >= 0; col--) {
                if (prev_b[row][col] != 0) {
                    if (mergeable) {
                        if (prev_b[row][col] == cur_b[row][cur_pos]) {
                            cur_b[row][cur_pos] *= 2;
                            mergeable = false;
                            continue;
                        }
                    }
                    cur_b[row][--cur_pos] = prev_b[row][col];
                    mergeable = true;
                }
            }
            cur_pos--;
            while (cur_pos >= 0) {
                cur_b[row][cur_pos--] = 0;
            }
        }
        break;
    case DOWN:
        for (int col = 0; col < n; col++) {
            cur_pos = n;
            mergeable = false;
            for (int row = n - 1; row >= 0; row--) {
                if (prev_b[row][col] != 0) {
                    if (mergeable) {
                        if (prev_b[row][col] == cur_b[cur_pos][col]) {
                            cur_b[cur_pos][col] *= 2;
                            mergeable = false;
                            continue;
                        }
                    }
                    cur_b[--cur_pos][col] = prev_b[row][col];
                    mergeable = true;
                }
            }
            cur_pos--;
            while (cur_pos >= 0) {
                cur_b[cur_pos--][col] = 0;
            }
        }
        break;
    case LEFT:
        for (int row = 0; row < n; row++) {
            cur_pos = -1;
            mergeable = false;
            for (int col = 0; col < n; col++) {
                if (prev_b[row][col] != 0) {
                    if (mergeable) {
                        if (prev_b[row][col] == cur_b[row][cur_pos]) {
                            cur_b[row][cur_pos] *= 2;
                            mergeable = false;
                            continue;
                        }
                    }
                    cur_b[row][++cur_pos] = prev_b[row][col];
                    mergeable = true;
                }
            }
            cur_pos++;
            while (cur_pos < n) {
                cur_b[row][cur_pos++] = 0;
            }
        }
    }
}

void brute_force(int stage) {
    if (stage == 6) {
        const auto& board = boards[5];
        int cur_max = 0;
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                if (board[row][col] > cur_max) {
                    cur_max = board[row][col];
                }
            }
        }
        if (cur_max > max_block) {
            max_block = cur_max;
        }
        return;
    }
    for (int d = 0; d < 4; d++) {
        run_stage(stage, (Direction)d);
        brute_force(stage + 1);
    }
}

int main() {
    scanf("%d", &n);

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            scanf("%d", &boards[0][row][col]);
        }
    }

    brute_force(1);

    printf("%d\n", max_block);

    return 0;
}

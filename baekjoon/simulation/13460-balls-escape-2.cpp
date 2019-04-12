// Implemented for multiple balls uselessly (not a good solution)
#include <cstdio>

using namespace std;

constexpr int N_MAX = 10;
constexpr int M_MAX = 10;
constexpr int STAGE_MAX = 10;
constexpr int INIT_MIN_STAGE_NUM = 100;

enum Direction : int { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 };
enum StageResult : int { NOTHING = 0, FAILED = 1, FINISHED = 2 };

int n, m;
char boards[STAGE_MAX + 1][N_MAX][M_MAX];
int min_stage_num = INIT_MIN_STAGE_NUM;

StageResult run_stage(int stage, Direction d) {
    const auto& prev_b = boards[stage - 1];
    auto& cur_b = boards[stage];
    int pos;
    bool red_consumed = false;

    switch (d) {
    case UP:
        for (int col = 1; col < m - 1; col++) {
            pos = 0;
            for (int row = 1; row < n; row++) {
                switch (prev_b[row][col]) {
                default:
                    break;
                case '#':
                    while (pos < row - 1) {
                        cur_b[++pos][col] = '.';
                    }
                    cur_b[++pos][col] = '#';
                    break;
                case 'O':
                    while (pos < row - 1) {
                        cur_b[++pos][col] = '.';
                    }
                    cur_b[++pos][col] = 'O';
                    break;
                case 'R':
                    if (cur_b[pos][col] == 'O') {
                        red_consumed = true;
                    } else {
                        cur_b[++pos][col] = 'R';
                    }
                    break;
                case 'B':
                    if (cur_b[pos][col] == 'O') {
                        return FAILED;
                    } else {
                        cur_b[++pos][col] = 'B';
                    }
                }
            }
        }
        break;
    case RIGHT:
        for (int row = 1; row < n - 1; row++) {
            pos = m - 1;
            for (int col = m - 2; col >= 0; col--) {
                switch (prev_b[row][col]) {
                default:
                    break;
                case '#':
                    while (pos > col + 1) {
                        cur_b[row][--pos] = '.';
                    }
                    cur_b[row][--pos] = '#';
                    break;
                case 'O':
                    while (pos > col + 1) {
                        cur_b[row][--pos] = '.';
                    }
                    cur_b[row][--pos] = 'O';
                    break;
                case 'R':
                    if (cur_b[row][pos] == 'O') {
                        red_consumed = true;
                    } else {
                        cur_b[row][--pos] = 'R';
                    }
                    break;
                case 'B':
                    if (cur_b[row][pos] == 'O') {
                        return FAILED;
                    } else {
                        cur_b[row][--pos] = 'B';
                    }
                }
            }
        }
        break;
    case DOWN:
        for (int col = 1; col < m - 1; col++) {
            pos = n - 1;
            for (int row = n - 2; row >= 0; row--) {
                switch (prev_b[row][col]) {
                default:
                    break;
                case '#':
                    while (pos > row + 1) {
                        cur_b[--pos][col] = '.';
                    }
                    cur_b[--pos][col] = '#';
                    break;
                case 'O':
                    while (pos > row + 1) {
                        cur_b[--pos][col] = '.';
                    }
                    cur_b[--pos][col] = 'O';
                    break;
                case 'R':
                    if (cur_b[pos][col] == 'O') {
                        red_consumed = true;
                    } else {
                        cur_b[--pos][col] = 'R';
                    }
                    break;
                case 'B':
                    if (cur_b[pos][col] == 'O') {
                        return FAILED;
                    } else {
                        cur_b[--pos][col] = 'B';
                    }
                }
            }
        }
        break;
    case LEFT:
        for (int row = 1; row < n - 1; row++) {
            pos = 0;
            for (int col = 1; col < m; col++) {
                switch (prev_b[row][col]) {
                default:
                    break;
                case '#':
                    while (pos < col - 1) {
                        cur_b[row][++pos] = '.';
                    }
                    cur_b[row][++pos] = '#';
                    break;
                case 'O':
                    while (pos < col - 1) {
                        cur_b[row][++pos] = '.';
                    }
                    cur_b[row][++pos] = 'O';
                    break;
                case 'R':
                    if (cur_b[row][pos] == 'O') {
                        red_consumed = true;
                    } else {
                        cur_b[row][++pos] = 'R';
                    }
                    break;
                case 'B':
                    if (cur_b[row][pos] == 'O') {
                        return FAILED;
                    } else {
                        cur_b[row][++pos] = 'B';
                    }
                }
            }
        }
    }

    if (red_consumed) {
        return FINISHED;
    } else {
        return NOTHING;
    }
}

void brute_force(int stage, int prev_d) {
    if (stage < min_stage_num && stage <= STAGE_MAX) {
        for (int d = 0; d < 4; d++) {
            if (d == prev_d) {
                continue;
            }
            StageResult result = run_stage(stage, (Direction)d);
            switch (result) {
            case NOTHING:
                brute_force(stage + 1, d);
                break;
            case FAILED:
                break;
            case FINISHED:
                if (stage < min_stage_num) {
                    min_stage_num = stage;
                }
                return;
            }
        }
    }
}

int main() {
    char buf[M_MAX + 2];

    scanf("%d%d ", &n, &m);

    for (int col = 1; col < m - 1; col++) {
        for (int i = 1; i <= STAGE_MAX; i++) {
            boards[i][0][col] = '#';
            boards[i][n - 1][col] = '#';
        }
    }

    for (int row = 0; row < n; row++) {
        fgets(buf, M_MAX + 2, stdin);
        for (int col = 0; col < m; col++) {
            boards[0][row][col] = buf[col];
        }
        for (int i = 1; i <= STAGE_MAX; i++) {
            boards[i][row][0] = '#';
            boards[i][row][m - 1] = '#';
        }
    }

    brute_force(1, -1);

    if (min_stage_num == INIT_MIN_STAGE_NUM) {
        printf("-1\n");
    } else {
        printf("%d\n", min_stage_num);
    }

    return 0;
}

#include <cstdio>

constexpr int LENGTH = 101;
constexpr int DY[4] = {0, -1, 0, 1};
constexpr int DX[4] = {1, 0, -1, 0};

int space[LENGTH][LENGTH] = {0};  // [y][x]

int start_y;
int start_x;
int end_y;
int end_x;
int curve_start = 1;
int curve_end = 1;

void process() {
    curve_end++;
    for (auto y = 0; y < LENGTH; y++) {
        for (auto x = 0; x < LENGTH; x++) {
            if (space[y][x] >= curve_start && space[y][x] < curve_end) {
                auto ny = x - end_x + end_y;
                auto nx = -y + end_x + end_y;
                if (nx >= 0 && nx < LENGTH && ny >= 0 && ny < LENGTH) {
                    if (space[ny][nx] < curve_start) {
                        space[ny][nx] = curve_end;
                    }
                }
            }
        }
    }
    auto nend_y = start_x - end_x + end_y;
    auto nend_x = -start_y + end_x + end_y;
    end_y = nend_y;
    end_x = nend_x;
}

int main() {
    int n;
    scanf("%d", &n);

    for (auto i = 0; i < n; i++) {
        int direct, gen;
        scanf("%d%d%d%d", &start_x, &start_y, &direct, &gen);
        end_y = start_y + DY[direct];
        end_x = start_x + DX[direct];
        space[start_y][start_x] = curve_start;
        space[end_y][end_x] = curve_start;
        for (auto j = 0; j < gen; j++) {
            process();
        }
        curve_start = (curve_end / 100) * 100 + 101;
        curve_end = curve_start;
    }

    int count = 0;
    for (auto y = 0; y < LENGTH - 1; y++) {
        for (auto x = 0; x < LENGTH - 1; x++) {
            if (space[y][x] != 0 && space[y][x + 1] != 0 && space[y + 1][x] != 0
                && space[y + 1][x + 1] != 0) {
                count++;
            }
        }
    }
    printf("%d\n", count);

    return 0;
}

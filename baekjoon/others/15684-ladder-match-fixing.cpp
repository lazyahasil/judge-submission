#include <algorithm>
#include <cstdio>

using namespace std;

constexpr int MAX_N = 10;
constexpr int MAX_H = 30;

int n;
int m;
int h;
int added = 0;
int min_added = 4;

int lad[MAX_H + 1][MAX_N + 1] = {0};
int loc[MAX_N + 1] = {0};

bool unaligned;

void explore_ladder(int row, int col) {
    if (col == n) {
        if (row == h) {
            unaligned = false;
            while (col > 0) {
                if (loc[col] != col) {
                    unaligned = true;
                    break;
                }
                col--;
            }
            if (!unaligned) {
                if (added < min_added) {
                    min_added = added;
                }
            }
        } else {
            explore_ladder(row + 1, 1);
        }
    } else {
        if (lad[row][col]) {
            swap(loc[col], loc[col + 1]);
            explore_ladder(row, col + 1);
            swap(loc[col], loc[col + 1]);
        } else {
            explore_ladder(row, col + 1);
            if (lad[row][col - 1] == 0 && lad[row][col + 1] == 0 && added < min_added - 1) {
                lad[row][col] = 2;
                swap(loc[col], loc[col + 1]);
                added++;
                explore_ladder(row, col + 1);
                added--;
                swap(loc[col], loc[col + 1]);
                lad[row][col] = 0;
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &h);

    for (int i = 0; i < m; i++) {
        int row, col;
        scanf("%d%d", &row, &col);
        lad[row][col] = 1;
    }

    for (int col = 1; col <= n; col++) {
        loc[col] = col;
    }

    explore_ladder(1, 1);

    if (min_added != 4) {
        printf("%d\n", min_added);
    } else {
        printf("-1\n");
    }

    return 0;
}

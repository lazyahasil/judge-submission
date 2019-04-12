#include <cstdio>
#include <cstdlib>

constexpr int N_MAX = 20;

int n;
int abilities[N_MAX][N_MAX] = {0};
int flags[N_MAX] = {0};
int min_diff = 1000000000;

void calculate() {
    int a = 0, b = 0, diff;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (flags[i] == flags[j]) {
                if (flags[i]) {
                    a += abilities[i][j];
                } else {
                    b += abilities[i][j];
                }
            }
        }
    }
    diff = abs(a - b);
    if (diff < min_diff) {
        min_diff = diff;
    }
}

void combination(int q, int r) {
    if (q < r) {
        return;
    }
    if (q <= 0 || r <= 0) {
        calculate();
        return;
    }
    flags[q - 1] = 1;
    combination(q - 1, r - 1);
    flags[q - 1] = 0;
    combination(q - 1, r);
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int t;
            scanf("%d", &t);
            abilities[j][i] += t;
        }
        for (int j = i; j < n; j++) {
            scanf("%d", &abilities[i][j]);
        }
    }

    combination(n, n / 2);

    printf("%d\n", min_diff);

    return 0;
}

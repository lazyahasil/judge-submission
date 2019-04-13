#include <cstdio>

using namespace std;

enum Orientation : int { HORZ = 0, VERT = 1, DIAG = 2 };

constexpr int N_MAX = 16;

int n;
int area[N_MAX + 2][N_MAX + 2];
int routes = 0;

void brute_force(int hrow, int hcol, Orientation orient) {
    if (hrow == n && hcol == n) {
        routes++;
    } else {
        if (orient != VERT && !area[hrow][hcol + 1]) {
            brute_force(hrow, hcol + 1, HORZ);
        }
        if (orient != HORZ && !area[hrow + 1][hcol]) {
            brute_force(hrow + 1, hcol, VERT);
        }
        if (!area[hrow][hcol + 1] && !area[hrow + 1][hcol] && !area[hrow + 1][hcol + 1]) {
            brute_force(hrow + 1, hcol + 1, DIAG);
        }
    }
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i <= n + 1; i++) {
        area[i][0] = 1;
        area[i][n + 1] = 1;
        area[0][i] = 1;
        area[n + 1][i] = 1;
    }

    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= n; col++) {
            scanf("%d", &area[row][col]);
        }
    }

    brute_force(1, 2, HORZ);

    printf("%d\n", routes);

    return 0;
}

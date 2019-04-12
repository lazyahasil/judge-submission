#include <cstdio>
#include <cstdlib>

using namespace std;

constexpr int BIG_NUMBER = 100000;

enum PlaceType : int {
    EMPTY = 0,
    HOUSE = 1,
    REST = 2,
};

int n;
int m;
PlaceType area[50][50];
int rest_count = 0;
int rest_rows[13];
int rest_cols[13];
bool flags[13];
int min_dist = BIG_NUMBER;

void calculate_chicken_dist() {
    int dist = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (area[row][col] == HOUSE) {
                int a_dist = BIG_NUMBER;
                for (int ri = 0; ri < rest_count; ri++) {
                    if (flags[ri]) {
                        int r_dist = abs(rest_rows[ri] - row) + abs(rest_cols[ri] - col);
                        if (r_dist < a_dist) {
                            a_dist = r_dist;
                        }
                    }
                }
                dist += a_dist;
            }
        }
    }
    if (dist < min_dist) {
        min_dist = dist;
    }
}

void combination(int n, int r) {
    if (n < r) {
        return;
    }
    if (n <= 0 || r <= 0) {
        calculate_chicken_dist();
        return;
    }
    flags[n - 1] = true;
    combination(n - 1, r - 1);
    flags[n - 1] = false;
    combination(n - 1, r);
}

int main() {
    scanf("%d%d", &n, &m);

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            PlaceType type;
            scanf("%d", (int*)&type);
            if (type == REST) {
                rest_rows[rest_count] = row;
                rest_cols[rest_count] = col;
                rest_count++;
            }
            area[row][col] = type;
        }
    }

    if (rest_count > m) {
        combination(rest_count, m);
    } else {
        for (int ri = 0; ri < rest_count; ri++) {
            flags[ri] = true;
        }
        calculate_chicken_dist();
    }

    printf("%d\n", min_dist);

    return 0;
}

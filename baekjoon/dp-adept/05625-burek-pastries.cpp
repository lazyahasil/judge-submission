// Data sets can be found on http://hsin.hr/coci/archive/2012_2013/
#include <cstdio>

using namespace std;

constexpr int MAX = 1000000;

int dp_x[MAX + 1] = {0};
int dp_y[MAX + 1] = {0};

void read_and_fill_dp(int n) {
    for (int i = 0; i < n; i++) {
        int x_min = MAX, x_max = 0, y_min = MAX, y_max = 0;

        for (int j = 0; j < 3; j++) {
            int x, y;
            scanf("%d %d", &x, &y);

            if (x_min > x) x_min = x;
            if (x_max < x) x_max = x;
            if (y_min > y) y_min = y;
            if (y_max < y) y_max = y;
        }

        dp_x[x_min + 1]++;
        dp_x[x_max]--;
        dp_y[y_min + 1]++;
        dp_y[y_max]--;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    read_and_fill_dp(n);

    for (int i = 1; i <= MAX; i++) {
        dp_x[i] += dp_x[i - 1];
        dp_y[i] += dp_y[i - 1];
    }

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        char axis_name;
        int c;
        scanf(" %c = %d", &axis_name, &c);
        if (axis_name == 'x') {
            printf("%d\n", dp_x[c]);
        } else {
            printf("%d\n", dp_y[c]);
        }
    }

    return 0;
}

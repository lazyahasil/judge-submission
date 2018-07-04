// Data sets can be found on http://hsin.hr/coci/archive/2012_2013/
#include <iostream>
#include <tuple>

using namespace std;

constexpr int k_max = 1000000;

int left_v[2][k_max + 1] = {0};
int right_v[2][k_max + 1] = {0};

void read_and_cut_pastries(int n) {
    for (int i = 0; i < n; i++) {
        int x_min = k_max, x_max = 0, y_min = k_max, y_max = 0;

        for (int j = 0; j < 3; j++) {
            int x, y;
            cin >> x >> y;

            if (x_min > x) x_min = x;
            if (x_max < x) x_max = x;
            if (y_min > y) y_min = y;
            if (y_max < y) y_max = y;
        }

        left_v[0][x_max]++;
        left_v[1][y_max]++;
        right_v[0][x_min]++;
        right_v[1][y_min]++;
    }
}

void align_values() {
    for (int i = 1; i <= k_max; i++) {
        left_v[0][i] += left_v[0][i - 1];
        left_v[1][i] += left_v[1][i - 1];
    }
    for (int i = k_max - 1; i >= 0; i--) {
        right_v[0][i] += right_v[0][i + 1];
        right_v[1][i] += right_v[1][i + 1];
    }
}

int main() {
    int n;

    scanf("%d", &n);
    read_and_cut_pastries(n);
    align_values();

    int m, c;
    char axis_name;

    cin >> m;
    for (int i = 0; i < m; i++) {
        scanf(" %c = %d", &axis_name, &c);
        int axis_select = axis_name == 'y';
        printf("%d\n", n - left_v[axis_select][c] - right_v[axis_select][c]);
    }

    return 0;
}

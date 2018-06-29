#include <iostream>

using namespace std;

using FacT = unsigned long long;

int main() {
    FacT n, k;
    FacT fac = 1;
    FacT fs[3][2] = {0, 1, 0, 1, 0, 1};

    cin >> n >> k;

    fs[0][0] = k;
    fs[1][0] = n - k;
    fs[2][0] = n;

    for (FacT i = 2; i <= n; i++) {
        fac *= i;

        for (int j = 0; j < 3; j++) {
            if (i == fs[j][0]) {
                fs[j][1] = fac;
            }
        }
    }

    cout << (fs[2][1] / (fs[0][1] * fs[1][1]));

    return 0;
}

#include <iostream>

using namespace std;

int main() {
    int n, k;
    int** bc;

    cin >> n >> k;

    bc = new int*[n + 1];
    for (auto i = 0; i <= n; i++) {
        bc[i] = new int[i + 1];
        bc[i][0] = bc[i][i] = 1;
    }

    for (auto i = 2; i <= n; i++) {
        for (auto j = 1; j < i; j++) {
            bc[i][j] = (bc[i - 1][j - 1] + bc[i - 1][j]) % 10007;
        }
    }

    cout << bc[n][k];

    // for (auto i = 0; i <= n; i++) {
    //     delete bc[i];
    // }
    // delete bc;

    return 0;
}

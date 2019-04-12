#include <iostream>

using namespace std;

int main() {
    int n;
    unsigned long long fa = 0ULL, fb = 1ULL;
    bool reverse = false;

    cin >> n;

    for (auto i = 0; i < n; i++) {
        if (!reverse) {
            fb = fa + fb;
            reverse = true;
        } else {
            fa = fa + fb;
            reverse = false;
        }
    }

    if (!reverse) {
        cout << fa;
    } else {
        cout << fb;
    }

    return 0;
}

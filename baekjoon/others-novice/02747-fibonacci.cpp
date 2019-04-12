#include <iostream>

using namespace std;

int main() {
    int n;
    int fa = 0, fb = 1;
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

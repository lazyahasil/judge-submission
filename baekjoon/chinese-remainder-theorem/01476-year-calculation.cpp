// This can be solved by Brute force
#include <array>
#include <iostream>
#include <numeric>
#include <tuple>

using namespace std;

constexpr int N = 3;
constexpr int M = 15 * 28 * 19;

constexpr array<int, N> m{15, 28, 19};
constexpr array<int, N> n{28 * 19, 15 * 19, 15 * 28};

// By the extended Euclidian algorithm
int modular_inverse(int a, int p) {
    if (a < p || p == 1) return 0;

    int b = p, t0 = 0, t1 = 1, temp;
    
    while (a > 1 && b != 0) {
        auto q = a / b;

        temp = b;
        b = a % b;
        a = temp;

        // t_i = t_(i-1) - q * t_(i-2)
        temp = t0;
        t0 = t1 - q * t0;
        t1 = temp;
    }

    if (a != 1) return 0;

    // Prevent a negative number
    return (t1 % p + p) % p;
}

int main() {
    int x = 0;

    for (auto i = 0; i < N; i++) {
        int ai, si, mi = m[i], ni = n[i];

        cin >> ai;

        // Congruence: nk * sk === 1 (mod mk)
        si = modular_inverse(ni, mi);

        x += ai * ni * si;
    }

    // Find the smallest x
    x %= M;
    if (x == 0) x = M;

    cout << x << "\n";

    return 0;
}

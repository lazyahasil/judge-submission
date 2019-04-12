// This can be solved by DP
#include <cstdio>

using namespace std;

constexpr int N_MAX = 15;

int n;
int t[N_MAX + 1];
int p[N_MAX + 1];
int m[N_MAX + 2];

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &t[i], &p[i]);
    }

    m[1] = 0;
    for (int i = 2; i <= n + 1; i++) {
        m[i] = 0;
        for (int j = 1; j < i; j++) {
            if (j + t[j] <= i) {
                int d = m[j] + p[j];
                if (d > m[i]) {
                    m[i] = d;
                }
            }
        }
    }

    printf("%d\n", m[n + 1]);

    return 0;
}

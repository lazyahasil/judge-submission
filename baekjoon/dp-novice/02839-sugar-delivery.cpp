#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

vector<int> opt_counts;

int main() {
    int n;

    scanf("%d", &n);
    opt_counts.resize(n + 1, -1);

    opt_counts[3] = 1;
    opt_counts[5] = 1;

    for (int i = 6; i <= n; i++) {
        if (opt_counts[i - 3] != -1) {
            if (opt_counts[i - 5] != -1) {
                opt_counts[i] = min(opt_counts[i - 3], opt_counts[i - 5]) + 1;
            } else {
                opt_counts[i] = opt_counts[i - 3] + 1;
            }
        } else if (opt_counts[i - 5] != -1) {
            opt_counts[i] = opt_counts[i - 5] + 1;
        }
    }

    printf("%d\n", opt_counts[n]);

    return 0;
}

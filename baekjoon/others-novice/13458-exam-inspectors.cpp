#include <cstdio>

using namespace std;

constexpr int MAX_TAKER_COUNT = 1000000;

int n;
int p;            // The primary's capacity
int s;            // The secondary's capacity
int* cc;          // Exam center count per exam taker count
long long r = 0;  // Result

int main() {
    cc = new int[MAX_TAKER_COUNT + 1]();

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int takers;
        scanf("%d", &takers);
        cc[takers]++;
    }

    scanf("%d%d", &p, &s);

    for (int i = 1; i <= p; i++) {
        r += cc[i];
    }

    int i = p + 1;
    int c = 2;
    while (i <= MAX_TAKER_COUNT - s + 1) {
        for (int j = 0; j < s; j++) {
            r += (long long)cc[i + j] * c;
        }
        i += s;
        c++;
    }
    for (int j = i; j <= MAX_TAKER_COUNT; j++) {
        r += (long long)cc[j] * c;
    }

    printf("%lld\n", r);

    return 0;
}

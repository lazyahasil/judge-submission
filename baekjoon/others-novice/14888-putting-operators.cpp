#include <cstdio>

using namespace std;

constexpr int N_MAX = 11;

enum Operator : int {
    PLUS = 0,
    MINUS = 1,
    TIMES = 2,
    DIVIDE = 3,
};

int n;
int operands[N_MAX];
int operat_counts[4];
Operator operat_symbols[N_MAX - 1];
int min_result = 1000000001;
int max_result = -1000000001;

void calculate() {
    int result = operands[0];
    for (int i = 0; i < n - 1; i++) {
        switch (operat_symbols[i]) {
        case PLUS:
            result += operands[i + 1];
            break;
        case MINUS:
            result -= operands[i + 1];
            break;
        case TIMES:
            result *= operands[i + 1];
            break;
        case DIVIDE:
            result /= operands[i + 1];
        }
    }
    if (result < min_result) {
        min_result = result;
    }
    if (result > max_result) {
        max_result = result;
    }
}

void permutation(int idx) {
    if (idx == n - 1) {
        calculate();
        return;
    }
    for (int j = 0; j < 4; j++) {
        if (operat_counts[j] != 0) {
            operat_counts[j]--;
            operat_symbols[idx] = (Operator)j;
            permutation(idx + 1);
            operat_counts[j]++;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &operands[i]);
    }
    scanf("%d%d%d%d", &operat_counts[0], &operat_counts[1], &operat_counts[2], &operat_counts[3]);
    permutation(0);
    printf("%d\n%d\n", max_result, min_result);
    return 0;
}

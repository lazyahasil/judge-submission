#include <cstdio>

int k;

int wheel[4][8];
int loc[4] = {0};
int rotating[4];

void check_rotation(int wi, int orig_direct) {
    int i, d;

    rotating[wi] = orig_direct;

    i = wi;
    d = -orig_direct;
    while (i > 0) {
        int left = (loc[i - 1] + 2) % 8;
        int right = (loc[i] + 6) % 8;
        if (wheel[i - 1][left] == wheel[i][right]) {
            break;
        }
        rotating[i - 1] = d;
        d *= -1;
        i--;
    }

    i = wi;
    d = -orig_direct;
    while (i < 3) {
        int left = (loc[i] + 2) % 8;
        int right = (loc[i + 1] + 6) % 8;
        if (wheel[i][left] == wheel[i + 1][right]) {
            break;
        }
        rotating[i + 1] = d;
        d *= -1;
        i++;
    }
}

int main() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            char saw;
            scanf(" %c", &saw);
            wheel[i][j] = saw == '1';
        }
    }

    scanf("%d", &k);

    for (int i = 0; i < k; i++) {
        int wheel_idx, direction;
        scanf("%d%d", &wheel_idx, &direction);
        wheel_idx--;
        for (int j = 0; j < 4; j++) {
            rotating[j] = 0;
        }
        check_rotation(wheel_idx, direction);
        for (int j = 0; j < 4; j++) {
            if (rotating[j] == 1) {
                loc[j] = (loc[j] + 7) % 8;
            } else if (rotating[j] == -1) {
                loc[j] = (loc[j] + 1) % 8;
            }
        }
    }

    int score = 0;
    for (int i = 0; i < 4; i++) {
        int first_saw = wheel[i][loc[i]];
        score += first_saw ? (1 << i) : 0;
    }
    printf("%d\n", score);

    return 0;
}

#include <array>
#include <cstdio>
#include <vector>

using namespace std;

using Vec1D = vector<int>;
using Vec2D = vector<vector<int>>;

constexpr int TETROMINO_COUNT = 5;

const array<Vec2D, TETROMINO_COUNT> TETROMINOS{{
    {
        {1, 1, 1, 1},
    },
    {
        {1, 1},
        {1, 1},
    },
    {
        {1, 0},
        {1, 0},
        {1, 1},
    },
    {
        {1, 0},
        {1, 1},
        {0, 1},
    },
    {
        {1, 1, 1},
        {0, 1, 0},
    },
}};

constexpr array<bool, TETROMINO_COUNT> FLIPABLES{{
    false,
    false,
    true,
    true,
    false,
}};

constexpr array<bool, TETROMINO_COUNT> ROTATABLES{{
    true,
    false,
    true,
    true,
    true,
}};

Vec2D rotate_tetro(const Vec2D& t) {
    Vec2D t1;
    size_t orig_height = t.size(), orig_width = t[0].size();
    t1.reserve(orig_width);
    for (size_t i = 0; i < orig_width; i++) {
        Vec1D tt1;
        tt1.reserve(orig_height);
        for (size_t j = 0; j < orig_height; j++) {
            tt1.emplace_back(t[orig_height - j - 1][i]);
        }
        t1.emplace_back(move(tt1));
    }
    return t1;
}

Vec2D flip_tetro(const Vec2D& t) {
    Vec2D t1;
    size_t height = t.size(), width = t[0].size();
    t1.reserve(height);
    for (size_t i = 0; i < height; i++) {
        Vec1D tt1;
        tt1.reserve(width);
        for (size_t j = 0; j < width; j++) {
            tt1.emplace_back(t[i][width - j - 1]);
        }
        t1.emplace_back(move(tt1));
    }
    return t1;
}

int n;
int m;
int** area;
int max_sum = 0;

void cover_with_tetro(const Vec2D& t) {
    int height = t.size(), width = t[0].size();
    for (int i = 0; i <= n - height; i++) {
        for (int j = 0; j <= m - width; j++) {
            int sum = 0;
            for (int k = 0; k < height; k++) {
                for (int l = 0; l < width; l++) {
                    if (t[k][l]) {
                        sum += area[i + k][j + l];
                    }
                }
            }
            if (sum > max_sum) {
                max_sum = sum;
            }
        }
    }
}

void check_tetro_rotating(const Vec2D& t, bool rotatable) {
    cover_with_tetro(t);
    if (rotatable) {
        auto t1 = t;
        for (int j = 0; j < 3; j++) {
            t1 = rotate_tetro(t1);
            cover_with_tetro(t1);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);

    area = new int*[n];

    for (int i = 0; i < n; i++) {
        area[i] = new int[m];
        for (int j = 0; j < m; j++) {
            scanf("%d", &area[i][j]);
        }
    }

    for (int i = 0; i < TETROMINO_COUNT; i++) {
        const Vec2D& t0 = TETROMINOS[i];
        check_tetro_rotating(t0, ROTATABLES[i]);
        if (FLIPABLES[i]) {
            Vec2D t2 = flip_tetro(t0);
            check_tetro_rotating(t2, ROTATABLES[i]);
        }
    }

    printf("%d\n", max_sum);

    return 0;
}

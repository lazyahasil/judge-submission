#include <array>
#include <cstdio>
#include <cstring>
#include <tuple>
#include <vector>

using namespace std;

using Point = pair<int, int>;

constexpr array<pair<int, int>, 4> DIRECTIONS{{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

enum Cell : int {
    EMPTY = 0,
    COVERED = 1,
    WALL = 2,
};

struct Cctv {
    size_t row;
    size_t col;
    int type;

    Cctv(int row, int col, int type) : row(row), col(col), type(type) {}
};

int height;
int width;
Cell area[10][10];
int place_count = 0;
int max_coverage = 0;
int cur_coverage;

vector<Cctv> cctvs;
array<array<int, 4>, 8> sights;

void mark_linearly(size_t row, size_t col, Point direction) {
    while (true) {
        row += direction.first;
        col += direction.second;
        switch (area[row][col]) {
        case EMPTY:
            area[row][col] = COVERED;
            cur_coverage++;
            break;
        case WALL:
            return;
        case COVERED:
            break;
        }
    }
}

void update_area() {
    cur_coverage = 0;
    for (size_t i = 0; i < cctvs.size(); i++) {
        const auto& cctv = cctvs[i];
        auto& sight = sights[i];
        if (area[cctv.row][cctv.col] != COVERED) {
            area[cctv.row][cctv.col] = COVERED;
            cur_coverage++;
        }
        for (size_t j = 0; j < 4; j++) {
            if (sight[j]) {
                mark_linearly(cctv.row, cctv.col, DIRECTIONS[j]);
            }
        }
    }
    if (cur_coverage > max_coverage) {
        max_coverage = cur_coverage;
    }
}

void check_all_cases(size_t cctv_num) {
    if (cctv_num >= cctvs.size()) {
        update_area();
        for (int row = 1; row <= height; row++) {
            for (int col = 1; col <= width; col++) {
                if (area[row][col] == COVERED) {
                    area[row][col] = EMPTY;
                }
            }
        }
    } else {
        const auto& cctv = cctvs[cctv_num];
        auto& sight = sights[cctv_num];
        if (cctv.type == 5) {
            check_all_cases(cctv_num + 1);
        } else {
            check_all_cases(cctv_num + 1);
            for (size_t i = 0; i < 3; i++) {
                auto first_sight = sight[0];
                memcpy(&sight[0], &sight[1], 3 * sizeof(sight[0]));
                sight[3] = first_sight;
                check_all_cases(cctv_num + 1);
            }
        }
    }
}

int main() {
    scanf("%d%d", &height, &width);

    for (int row = 0; row <= height + 1; row++) {
        area[row][0] = WALL;
        area[row][width + 1] = WALL;
    }
    for (int col = 1; col <= width; col++) {
        area[0][col] = WALL;
        area[height + 1][col] = WALL;
    }

    for (int row = 1; row <= height; row++) {
        for (int col = 1; col <= width; col++) {
            int place;
            scanf("%d", &place);
            if (place == 0) {
                area[row][col] = EMPTY;
                place_count++;
            } else if (place == 6) {
                area[row][col] = WALL;
            } else {
                area[row][col] = EMPTY;
                place_count++;
                cctvs.emplace_back(Cctv(row, col, place));
                switch (place) {
                case 1:
                    sights[cctvs.size() - 1] = {1, 0, 0, 0};
                    break;
                case 2:
                    sights[cctvs.size() - 1] = {1, 0, 1, 0};
                    break;
                case 3:
                    sights[cctvs.size() - 1] = {1, 1, 0, 0};
                    break;
                case 4:
                    sights[cctvs.size() - 1] = {1, 1, 0, 1};
                    break;
                case 5:
                    sights[cctvs.size() - 1] = {1, 1, 1, 1};
                }
            }
        }
    }

    check_all_cases(0);

    printf("%d\n", place_count - max_coverage);

    return 0;
}

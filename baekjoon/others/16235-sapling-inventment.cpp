#include <algorithm>
#include <array>
#include <cstdio>
#include <forward_list>
#include <tuple>
#include <vector>

using namespace std;

using Point = pair<long, long>;

struct AgeSap {
    long age;
    forward_list<Point> saps;
};

const array<Point, 8> DIRECTIONS{{
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, -1},
    {0, 1},
    {1, -1},
    {1, 0},
    {1, 1},
}};

int n;
long** patches;
long** manures;
long** dead_nutrients;
vector<AgeSap*> age_saps;

void spring() {
    size_t age_saps_size = age_saps.size();

    for (size_t i = 0; i < age_saps_size; i++) {
        auto* age_sap = age_saps[i];
        long age = age_sap->age;
        auto& saps = age_sap->saps;

        auto before = saps.before_begin();
        for (auto it = saps.begin(); it != saps.end(); before = it, it++) {
            const auto& point = *it;
            if (patches[point.first][point.second] >= age) {
                patches[point.first][point.second] -= age;
            } else {
                dead_nutrients[point.first][point.second] += age / 2;
                saps.erase_after(before);
                it = before;
            }
        }

        if (saps.empty()) {
            delete age_sap;
            age_saps.erase(age_saps.begin() + i);
            age_saps_size--;
            i--;
        } else {
            age_sap->age++;
        }
    }
}

void summer() {
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            patches[i][j] += dead_nutrients[i][j];
            dead_nutrients[i][j] = 0;
        }
    }
}

void fall() {
    if (age_saps.empty()) {
        AgeSap* age_sap = new AgeSap;
        age_sap->age = 1;
        age_saps.insert(age_saps.begin(), age_sap);
    } else if (age_saps[0]->age != 1) {
        AgeSap* age_sap = new AgeSap;
        age_sap->age = 1;
        age_saps.insert(age_saps.begin(), age_sap);
    }

    auto& new_saps = age_saps[0]->saps;

    for (const auto* age_sap : age_saps) {
        long age = age_sap->age;
        if (age % 5 == 0) {
            const auto& saps = age_sap->saps;
            for (const auto& point : saps) {
                for (const auto& direction : DIRECTIONS) {
                    long new_row = point.first + direction.first;
                    long new_col = point.second + direction.second;
                    if (new_row >= 0 && new_row < n && new_col >= 0 && new_col < n) {
                        new_saps.emplace_front(make_pair(new_row, new_col));
                    }
                }
            }
        }
    }
}

void winter() {
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            patches[i][j] += manures[i][j];
        }
    }
}

void push_sap_at_first(long age, const Point& point) {
    size_t idx = 0;
    while (idx < age_saps.size()) {
        long cur_age = age_saps[idx]->age;
        if (cur_age > age) {
            break;
        }
        if (cur_age == age) {
            age_saps[idx]->saps.emplace_front(point);
            return;
        }
        idx++;
    }
    AgeSap* age_sap = new AgeSap;
    age_sap->age = age;
    age_sap->saps.emplace_front(point);
    age_saps.insert(age_saps.begin() + idx, age_sap);
}

int main() {
    int m, k;

    scanf("%d%d%d", &n, &m, &k);

    patches = new long*[n];
    manures = new long*[n];
    dead_nutrients = new long*[n];
    for (auto i = 0; i < n; i++) {
        patches[i] = new long[n];
        manures[i] = new long[n];
        dead_nutrients[i] = new long[n]();
        for (auto j = 0; j < n; j++) {
            patches[i][j] = 5;
        }
    }

    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < n; j++) {
            scanf("%ld", &manures[i][j]);
        }
    }

    for (auto i = 0; i < m; i++) {
        long row, col, age;
        scanf("%ld%ld%ld", &row, &col, &age);
        row--;
        col--;
        push_sap_at_first(age, make_pair(row, col));
    }

    for (auto i = 0; i < k; i++) {
        spring();
        summer();
        fall();
        winter();
    }

    size_t count = 0;
    for (const auto* age_sap : age_saps) {
        const auto& saps = age_sap->saps;
        for (auto it = saps.begin(); it != saps.end(); it++) {
            count++;
        }
    }
    printf("%lu\n", count);

    return 0;
}

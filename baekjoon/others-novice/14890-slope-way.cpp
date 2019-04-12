#include <cstdio>
#include <tuple>
#include <vector>

using namespace std;

int n;
int l;
int valid_count = 0;

vector<pair<int, int>> hori_way;
array<vector<pair<int, int>>, 100> vert_ways;

void update_way(vector<pair<int, int>>& way, int height) {
    if (way.empty()) {
        way.emplace_back(make_pair(height, 1));
    } else {
        if (way[way.size() - 1].first == height) {
            way[way.size() - 1].second++;
        } else {
            way.emplace_back(make_pair(height, 1));
        }
    }
}

void validate_way(vector<pair<int, int>>& way) {
    for (size_t i = 1; i < way.size(); i++) {
        int diff = way[i - 1].first - way[i].first;
        switch (diff) {
        case -1:
            if (way[i - 1].second < l) {
                return;
            }
            break;
        case 1:
            if (way[i].second < l) {
                return;
            }
            way[i].second -= l;
            break;
        default:
            return;
        }
    }
    valid_count++;
}

int main() {
    scanf("%d%d", &n, &l);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int height;
            scanf("%d", &height);
            update_way(hori_way, height);
            update_way(vert_ways[j], height);
        }
        validate_way(hori_way);
        hori_way.clear();
    }

    for (int i = 0; i < n; i++) {
        validate_way(vert_ways[i]);
    }

    printf("%d\n", valid_count);

    return 0;
}

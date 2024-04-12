#include <bits/stdc++.h>

using namespace std;
#define int intmax_t
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define fst first
#define snd second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;

int bfs(vector<vector<char>> &grid, int start_x, int start_y, int rows, int cols) {
    queue<pair<pii, int>> q;
    q.emplace(make_pair(start_x, start_y), 0);
    set<pair<pii, int>> visited;
    map<pair<pii, int>, int> distance_map;
    distance_map[{make_pair(start_x, start_y), 0}] = 0;
    visited.emplace(make_pair(start_x, start_y), 0);
    while (!q.empty()) {
        auto [pos, bitmask] = q.front();
        auto [x, y] = pos;
        q.pop();
        list<pii> neighbours{{x + 1, y},
                             {x - 1, y},
                             {x,     y + 1},
                             {x,     y - 1}};
        for (const auto &[neighbour_x, neighbour_y]: neighbours) {
            if (neighbour_x < 0 || neighbour_x >= rows
                || neighbour_y < 0 || neighbour_y >= cols
                || grid[neighbour_x][neighbour_y] == '#') continue;
            int newMask = bitmask;
            bool ok = true;
            switch (grid[neighbour_x][neighbour_y]) {
                case 'b':
                    newMask |= 0b0001;
                    break;
                case 'y':
                    newMask |= 0b0010;
                    break;
                case 'r':
                    newMask |= 0b0100;
                    break;
                case 'g':
                    newMask |= 0b1000;
                    break;
                case 'B':
                    if (!(newMask & 0b0001)) ok = false;
                    break;
                case 'Y':
                    if (!(newMask & 0b0010)) ok = false;
                    break;
                case 'R':
                    if (!(newMask & 0b0100)) ok = false;
                    break;
                case 'G':
                    if (!(newMask & 0b1000)) ok = false;
                    break;
            }
            if (ok && !visited.count({make_pair(neighbour_x, neighbour_y), newMask})) {
                q.emplace(make_pair(neighbour_x, neighbour_y), newMask);
                visited.emplace(make_pair(neighbour_x, neighbour_y), newMask);
                distance_map[{make_pair(neighbour_x, neighbour_y), newMask}] = distance_map[{pos, bitmask}] + 1;
            }
            if (grid[neighbour_x][neighbour_y] == 'X') {
                return distance_map[{make_pair(neighbour_x, neighbour_y), newMask}];
            }
        }
    }
    return -1;
}

void solve() {
    while (true) {
        int rows, cols;
        cin >> rows >> cols;
        vector<vector<char>> grid(rows, vector<char>(cols, '.'));
        if (!rows && !cols) break;
        int start_x = 0, start_y = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cin >> grid[i][j];
                if (grid[i][j] == '*') {
                    start_x = i, start_y = j;
                }
            }
        }
        auto distance = bfs(grid, start_x, start_y, rows, cols);
        if (distance != -1) {
            cout << "Escape possible in " << distance << " steps.\n";
        } else {
            cout << "The poor student is trapped!\n";
        }
    }

}

signed main() {
    std::istream::sync_with_stdio(false);
    cin.tie(nullptr);
//#undef int
//    signal(SIGSEGV, [](int) {
//        exit(0);
//    });
//#define int intmax_t
    int t = 1;
    //cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}



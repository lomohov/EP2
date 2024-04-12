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

using pos = tuple<int, int>;
void markDots(vector<vector<char>> & grid, int x, int y, int h, int w, queue<pos> & orig_q) {
    queue<pos> q;
    q.emplace(x, y);
    while(!q.empty()) {
        auto [curr_x, curr_y] = q.front();
        q.pop();
        list<pii> neighbours = {{curr_x + 1, curr_y},
                                {curr_x - 1, curr_y},
                                {curr_x,     curr_y + 1},
                                {curr_x,     curr_y - 1}};
        for (const auto &[pos_x, pos_y]: neighbours) {
            if (pos_x >= 0 && pos_x < h && pos_y >= 0 && pos_y < w) {
                if (grid[pos_x][pos_y] == 'X') {
                    q.emplace(pos_x, pos_y);
                    grid[pos_x][pos_y] = 'v';
                }
                if (grid[pos_x][pos_y] == '*') {
                    orig_q.emplace(pos_x, pos_y);
                }
            }
        }
    }
}
int bfs(vector<vector<char>> &grid, int x, int y, int h, int w) {
    int res = 0;
    queue<pos> q;
    if (grid[x][y] == 'X') {
        markDots(grid, x, y, h, w, q);
        res++;
    } else {
        q.emplace(x, y);
    }
    grid[x][y] = 'v';
    while (!q.empty()) {
        auto [curr_x, curr_y] = q.front();
        q.pop();
        list<pii> neighbours = {{curr_x + 1, curr_y},
                                {curr_x - 1, curr_y},
                                {curr_x,     curr_y + 1},
                                {curr_x,     curr_y - 1}};
        for (const auto &[pos_x, pos_y]: neighbours) {
            if (pos_x >= 0 && pos_x < h && pos_y >= 0 && pos_y < w) {
                if (grid[pos_x][pos_y] == '*') {
                    q.emplace(pos_x, pos_y);
                }
                if(grid[pos_x][pos_y] == 'X') {
                    grid[pos_x][pos_y] = 'v';
                    markDots(grid, pos_x, pos_y, h, w, q);
                    res++;
                }
                grid[pos_x][pos_y] = 'v';
            }
        }
    }
    return res;
}

void solve() {
    while (true) {
        int h, w;
        cin >> h >> w;
        vector<vector<char>> grid(h, vector<char>(w, '.'));
        if (!h && !w) {
            break;
        }
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                cin >> grid[i][j];
            }
        }
        vector<int> result;
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (grid[i][j] == 'X' || grid[i][j] == '*') {
                    auto count = bfs(grid, i, j, h, w);
                    if (count) result.push_back(count);
                }
            }
        }
        std::sort(all(result));
        cout << "Throw: ";
        for (int i = 0; i < sz(result); ++i) {
            if (!i) cout << result[i];
            else cout << " " << result[i];
        }
        cout << "\n";
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



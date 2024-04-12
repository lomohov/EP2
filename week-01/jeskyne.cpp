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

using pos = tuple<int_fast16_t, int_fast16_t, int_fast16_t>;

void solve() {
    int_fast16_t x, y, z;
    cin >> x >> y >> z;
    vector<vvi> grid(z, vvi(x, vi(y, 0)));
    queue<pos> q;
    int res = 0;
    for (int_fast16_t i = 0; i < z; ++i) {
        int_fast16_t p;
        cin >> p;
        for (int_fast16_t j = 0; j < p; ++j) {
            int_fast16_t r, s;
            cin >> r >> s;
            grid[i][r - 1][s - 1] = 1;
            if (i == 0) {
                q.emplace(0, r - 1, s - 1);
                res++;
                grid[0][r - 1][s - 1] = 2;
            }
        }
    }
    while (!q.empty()) {
        auto [curr_z, curr_x, curr_y] = q.front();
        q.pop();
        list<pos> neighbours = {{curr_z + 1, curr_x,     curr_y},
                                {curr_z - 1, curr_x,     curr_y},
                                {curr_z,     curr_x + 1, curr_y},
                                {curr_z,     curr_x - 1, curr_y},
                                {curr_z,     curr_x,     curr_y + 1},
                                {curr_z,     curr_x,     curr_y - 1}};
        for (const auto &[pos_z, pos_x, pos_y]: neighbours) {
            if (pos_z >= 0 && pos_z < z && pos_x >= 0 && pos_x < x && pos_y >= 0 && pos_y < y) {
                if (grid[pos_z][pos_x][pos_y] == 1) {
                    q.emplace(pos_z, pos_x, pos_y);
                    grid[pos_z][pos_x][pos_y] = 2;
                    res++;
                }
            }
        }
    }
    cout << "Je nutne vycerpat " << res * 1000 << " litru vody.\n";
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
    cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}



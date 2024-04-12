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

ld prim (vector<vector<pair<ld, int>>> & adj_list, int start) {
    priority_queue<pair<ld, int>, vector<pair<ld, int>>, greater<>> q;
    q.emplace(0.0, start);
    vector<bool> added (adj_list.size(), false);
    ld mst_cost = 0;
    while (!q.empty()) {
        auto [cost, node] = q.top();
        q.pop();
        if (!added[node]) {
            mst_cost += cost;
            added[node] = true;
            for (auto & [neighbour_cost, neighbour] : adj_list[node]) {
                if (!added[neighbour]) {
                    q.emplace(neighbour_cost, neighbour);
                }
            }
        }
    }
    return mst_cost;
}
void solve() {
    int n;
    cin >> n;
    vector<pair<ld, ld>> vertexes(n);
    for (int i = 0; i < n; ++i) {
        ld x, y;
        cin >> x >> y;
        vertexes[i] = {x, y};
    }
    vector<vector<pair<ld, int>>> adj_list (n, vector<pair<ld,int>>());
    for (int i = 0; i < n; ++i) {
        auto [x, y] = vertexes[i];
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            auto [x_ngb, y_ngb] = vertexes[j];
            adj_list[i].emplace_back(sqrt((x-x_ngb) * (x-x_ngb) + (y-y_ngb) * (y-y_ngb)),j);
        }
    }
    cout << fixed << setprecision(2) << prim(adj_list, 0) << "\n";
}
signed main() {
    std::istream::sync_with_stdio(false); cin.tie(nullptr);
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



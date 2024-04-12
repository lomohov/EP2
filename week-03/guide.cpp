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

vector<vector<int>> adj;

vector<bool> visited;
vector<int> tin, low;
set<int> articulations;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children = 0;
    for (int to: adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p != -1)
                articulations.emplace(v);
            ++children;
        }
    }
    if (p == -1 && children > 1)
        articulations.emplace(v);
}

void solve() {
    int counter = 1;
    while (true) {
        int n;
        cin >> n;
        if (!n) break;
        unordered_map<string, int> mapper;
        vector<string> inverse_mapper(n);
        for (int i = 0; i < n; ++i) {
            string city;
            cin >> city;
            mapper[city] = i;
            inverse_mapper[i] = city;
        }
        adj = vector(n, vi());
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            string from, to;
            cin >> from >> to;
            adj[mapper[from]].push_back(mapper[to]);
            adj[mapper[to]].push_back(mapper[from]);
        }
        timer = 0;
        visited.assign(n, false);
        tin.assign(n, -1);
        low.assign(n, -1);
        articulations = set<int>();
        for (int i = 0; i < n; ++i) {
            if (!visited[i])
                dfs(i);
        }
        cout << "City map #" << counter++ << ": " << articulations.size() << " camera(s) found\n";
        vector<string> articuls;
        articuls.reserve(articulations.size());
        for (const auto item: articulations) {
            articuls.push_back(inverse_mapper[item]);
        }
        sort(all(articuls));
        for (const auto &item: articuls) {
            cout << item << "\n";
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



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

vi topsort (vector<vector<int>> & graph, vi & indegrees, int n) {
    vi res;
    priority_queue<int, vi, greater<>> q;
    for (int i = 0; i < n; ++i) {
        if (!indegrees[i]) q.push(i);
    }
    while (!q.empty()) {
        auto vertex = q.top();
        q.pop();
        res.push_back(vertex);

        for (const auto neighbour: graph[vertex]) {
            indegrees[neighbour]--;
            if (indegrees[neighbour] == 0) q.push(neighbour);
        }
    }
    return res;
}
void solve() {
    int counter = 1;
    while (true) {
        int n;
        cin >> n;
        if (!n) break;
        unordered_map<string, int> mapper;
        vector<string> inverse_mapper (n);
        for (int i = 0; i < n; ++i) {
            string beverage;
            cin >> beverage;
            mapper[beverage] = i;
            inverse_mapper[i] = beverage;
        }
        vvi adj_list (n, vi());
        int m;
        cin >> m;
        vi indegrees (n, 0);
        for (int i = 0; i < m; ++i) {
            string from, to;
            cin >> from >> to;
            adj_list[mapper[from]].push_back(mapper[to]);
            indegrees[mapper[to]]++;
        }
        auto indexes = topsort(adj_list, indegrees, n);
        cout << "Case #" << counter << ": Dilbert should drink beverages in this order:";
        for (const auto &item: indexes) {
            cout << " " << inverse_mapper[item];
        }
        cout << ".\n";
        counter++;
    }
}
signed main() {
    std::istream::sync_with_stdio(false); cin.tie(nullptr);
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



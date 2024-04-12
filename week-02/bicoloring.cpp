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

bool bfs(vvi & graph, vector<char> & visited, int start) {
    queue<int> q;
    q.push(start);
    visited[start] = 'b';
    while (!q.empty()) {
        auto vertex = q.front();
        q.pop();
        auto color = visited[vertex];
        for (const auto neighbour: graph[vertex]) {
            if (visited[neighbour] == color) return false;
            if (visited[neighbour] == 'e') {
                q.push(neighbour);
                visited[neighbour] = color == 'b' ? 'w' : 'b';
            }
        }
    }
    return true;
}

void solve() {
    while (true) {
        int n, m;
        cin >> n;
        if (!n) break;
        cin >> m;
        vvi adj_list (n, vi());
        for (int i = 0; i < m; ++i) {
            int from, to;
            cin >> from >> to;
            adj_list[from].push_back(to);
            adj_list[to].push_back(from);
        }
        vector<char> visited (n, 'e');
        bool isBipartite = true;
        for (int i = 0; i < n; ++i) {
            if (visited[i] == 'e') isBipartite = bfs(adj_list, visited, i);
            if (!isBipartite) break;
        }
        cout << (isBipartite ? "YES" : "NO") << "\n";
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



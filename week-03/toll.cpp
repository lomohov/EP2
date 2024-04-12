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

int dijkstra(map<char, vector<char>> &adj_list, char start, char end, int start_weight) {
    if (start == end) return start_weight;
    map<char, int> distance;
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<>> q;
    q.emplace(start_weight, start);
    while (!q.empty()) {
        auto [curr_dist, vertex] = q.top();
        q.pop();

        int weight_neighbour = (isupper(vertex) ? (curr_dist + 18) / 19 : 1);
        for (const auto neighbour: adj_list[vertex]) {
            if (!distance.count(neighbour) || distance[neighbour] > curr_dist + weight_neighbour) {
                distance[neighbour] = curr_dist + weight_neighbour;
                q.emplace(distance[neighbour], neighbour);
            }
        }
    }
    return distance[end];
}

void solve() {
    int counter = 1;
    while (true) {
        int n;
        cin >> n;
        if (n == -1) break;
        map<char, vector<char>> graph;
        for (int i = 0; i < n; ++i) {
            char from, to;
            cin >> from >> to;
            graph[from].push_back(to);
            graph[to].push_back(from);
        }

        char start, end;
        int items;
        cin >> items >> start >> end;
        if (n == 0) {
            cout << "Case " << counter++ << ": 0\n";
            continue;
        }
        auto res = dijkstra(graph, end, start, items);
        cout << "Case " << counter++ << ": " << res << "\n";
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

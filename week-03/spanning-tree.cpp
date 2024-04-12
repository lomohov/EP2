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

pair<vii, int> prim (vector<vii> & adj_list, int start) {
    vii res;
    priority_queue<pii, vii, greater<>> q;
    q.emplace(0, start);
    vector<bool> added (adj_list.size(), false);
    int mst_cost = 0;
    while (!q.empty()) {
        auto [cost, node] = q.top();
        q.pop();
        if (!added[node]) {
            mst_cost += cost;
            added[node] = true;
            for (auto & [neighbour_cost, neighbour] : adj_list[node]) {
                if (!added[neighbour]) {
                    q.emplace(neighbour_cost, neighbour);
                    res.emplace_back(node, neighbour);
                }
            }
        }
    }
    return {res, mst_cost};
}
pair<int, list<int>> dijkstra (vector<vii> & adj_list, int start, int end) {
    list<int> res;
    vector<int> distance(adj_list.size(), INTMAX_MAX);
    map<pii, pii> parents;
    priority_queue<pii, vii, greater<>> q;
    q.emplace(0, start);
    distance[start] = 0;
    parents[{0, start}] = {-1, -1};
    while(!q.empty()) {
        auto [weight, vertex] = q.top();
        q.pop();
        for (const auto &[weight_neighbour, neighbour]: adj_list[vertex]) {
            if (distance[neighbour] > distance[vertex] + weight_neighbour) {
                distance[neighbour] = distance[vertex] + weight_neighbour;
                q.emplace(distance[neighbour], neighbour);
                parents[{distance[neighbour], neighbour}] = {weight, vertex};
            }
            if (neighbour == end) {
                auto curr = end;
                int dist = distance[curr];
                while (dist != -1) {
                    auto parent = parents[{distance[curr], curr}];
                    dist = parent.first;
                    curr = parent.second;
                    res.push_front(parent.second);
                }
                return {distance[end], res};
            }
        }
    }
    return {-1, {}};
}

void solve() {

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



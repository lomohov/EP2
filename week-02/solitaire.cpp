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
typedef pair<int_fast16_t, int_fast16_t> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;

using Points = tuple<pii, pii, pii, pii>;
namespace std {
    template<> struct hash<pii> {
        size_t operator()(const pii & p) const {
            auto h1 = std::hash<int_fast16_t >{}(p.first);
            auto h2 = std::hash<int_fast16_t >{}(p.second);
            return h1 * 31 ^ h2;
        }
    };
}

struct hashPoints {
    size_t operator()(const Points& points) const {
        size_t hash = 0;
        std::array<pii, 4> pointsArray = {std::get<0>(points), std::get<1>(points), std::get<2>(points), std::get<3>(points)};
        for (const auto& point : pointsArray) {
            hash ^= std::hash<pii>{}(point)  + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};
bool inBound(int_fast16_t x, int_fast16_t y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}
bool isValidNeighbour(const pii& candidate, const pii& point2, const pii& point3, const pii& point4) {
    return (candidate == point2 || candidate == point3 || candidate == point4);
}
Points sortPoints(const pii& p1, const pii& p2, const pii& p3, const pii& p4) {
    vector<pii> points = {p1, p2, p3, p4};
    sort(points.begin(), points.end());
    return make_tuple(points[0], points[1], points[2], points[3]);
}
void addStepOrTwoWayStep(const int_fast16_t i, const int_fast16_t j, const pii& point, vector<Points> & res, const pii& point2, const pii& point3, const pii& point4) {
    pii candidate(point.first + i, point.second + j);
    if (inBound(candidate.first, candidate.second)) {
        if (isValidNeighbour(candidate, point2, point3, point4)) {
            pii twoStepsAway(candidate.first + i, candidate.second + j);
            if (inBound(twoStepsAway.first, twoStepsAway.second) &&
                !isValidNeighbour(twoStepsAway, point2, point3, point4)) {
                res.emplace_back(sortPoints(twoStepsAway, point2, point3, point4));
            }
        } else {
            res.emplace_back(sortPoints(candidate, point2, point3, point4));
        }
    }
}

void getNeighbourForPoint(const pii& point, vector<Points> & res, const pii& point2, const pii& point3, const pii& point4) {
    addStepOrTwoWayStep(1,0,point, res, point2, point3, point4);
    addStepOrTwoWayStep(-1,0,point, res, point2, point3, point4);
    addStepOrTwoWayStep(0,1,point, res, point2, point3, point4);
    addStepOrTwoWayStep(0,-1,point, res, point2, point3, point4);
}

vector<Points> getNeighbours(const Points & points) {
    vector<Points> res;
    auto [point1, point2, point3, point4] = points;
    getNeighbourForPoint(point1, res, point2, point3, point4);
    getNeighbourForPoint(point2, res, point1, point3, point4);
    getNeighbourForPoint(point3, res, point1, point2, point4);
    getNeighbourForPoint(point4, res, point1, point2, point3);
    return res;
}

bool bfs (const Points & start_points, const Points & end_points) {
    queue<pair<Points, int_fast16_t >> q1, q2;
    unordered_set<Points, hashPoints> visited1;
    unordered_set<Points, hashPoints> visited2;
    q1.emplace(start_points, 0);
    q2.emplace(end_points, 0);
    visited1.emplace(start_points);
    visited2.emplace(end_points);
    while (!q1.empty()) {
        auto [points, counter] = q1.front();
        if (counter > 3) break;
        q1.pop();
        auto neighbours = getNeighbours(points);
        for (const auto &neighbour: neighbours) {
            if (visited1.count(neighbour)) continue;
            visited1.emplace(neighbour);
            q1.emplace(neighbour, counter+1);
            if (neighbour == end_points) {
                return true;
            }
        }
    }
    while (!q2.empty()) {
        auto [points, counter] = q2.front();
        if (counter > 3) break;
        q2.pop();
        auto neighbours = getNeighbours(points);
        for (const auto &neighbour: neighbours) {
            if (visited1.count(neighbour)) return true;
            if (visited2.count(neighbour)) continue;
            visited2.emplace(neighbour);
            q2.emplace(neighbour, counter+1);
            if (neighbour == start_points) {
                return true;
            }
        }
    }

    return false;
}

void solve() {
    while (true) {
        int_fast16_t a1, b1, c1, d1, e1, f1, g1, h1;
        if (!(cin >> a1 >> b1 >> c1 >> d1 >> e1 >> f1 >> g1 >> h1)) return;

        int_fast16_t a2, b2, c2, d2, e2, f2, g2, h2;
        if (!(cin >> a2 >> b2 >> c2 >> d2 >> e2 >> f2 >> g2 >> h2)) return;

        Points start_points ({a1, b1}, {c1, d1}, {e1, f1}, {g1, h1}),
               end_points   ({a2, b2}, {c2, d2}, {e2, f2}, {g2, h2});

        bool found = bfs(start_points, end_points) || bfs(end_points, start_points);
        cout << (found ? "YES" : "NO") << '\n';
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

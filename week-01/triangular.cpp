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
int getLineNumber(int vertex) {
    return static_cast<int>(sqrt(2 * vertex - (ld)1.0 / 4) - 1.0 / 2) + 1;
}
int getStartOfLine(int line) {
    return (line*(line-1))/2 + 1;
}
int getEndOfLine(int line) {
    return (line*(line+1))/2;
}
bool isOnSameLine(int vertex1, int vertex2) {
    return getLineNumber(vertex1) == getLineNumber(vertex2);
}
bool validateTriangleWithBase(int baseA, int baseB, int head) {
    auto diff = abs(baseA-baseB);
    auto lineNumber = getLineNumber(head);
    auto baseLineNumber = getLineNumber(baseA);
    if (baseLineNumber - lineNumber  == diff) {
        auto diffFromStartHead = head - getStartOfLine(lineNumber);
        auto diffFromStartBase = minmax(baseA,baseB).first - getStartOfLine(baseLineNumber);
        if (diffFromStartBase == diffFromStartHead) return true;
    }
    if (lineNumber - baseLineNumber == diff) {
        auto diffFromEndHead = getEndOfLine(lineNumber) - head;
        auto diffFromEndBase = getEndOfLine(baseLineNumber) - minmax(baseA,baseB).first;
        if (diffFromEndBase == diffFromEndHead) return true;
    }
    return false;
}
bool validateTriangle(const vi & coords) {
    auto a = coords[0];
    auto b = coords[1];
    auto c = coords[2];
    if (isOnSameLine(a,b)) {
        if (validateTriangleWithBase(a,b,c)) return true;
    }
    if (isOnSameLine(b,c)) {
        if (validateTriangleWithBase(b, c, a)) return true;
    }
    if (isOnSameLine(a,c)) {
        if (validateTriangleWithBase(a, c, b)) return true;
    }

    return false;
}
bool validateParallelogram(vi & coords) {
    std::sort(all(coords));
    auto a = coords[0];
    auto b = coords[1];
    auto c = coords[2];
    auto d = coords[3];
    return (validateTriangle({a,b,c}) && validateTriangle({b,c,d}))
        || (validateTriangle({a, c, d}) && validateTriangle({a,b,d}));
}
bool validateHexagon(vi & coords) {
    std::sort(all(coords));
    auto a = coords[0];
    auto b = coords[1];
    auto c = coords[2];
    auto d = coords[3];
    auto e = coords[4];
    auto f = coords[5];
    auto lengthA = b-a;
    auto lengthB = d-c;
    auto lengthC = f-e;
    if (2*lengthA != lengthB || lengthA != lengthC) return false;

    auto center = c + lengthA;
    return validateTriangle({a,b,center})
        && validateTriangle({a,c, center})
        && validateTriangle({b, center, d})
        && validateTriangle({c, e, center})
        && validateTriangle({e, f, center})
        && validateTriangle({d, f, center});
}

void solve() {
    for (string line; getline(cin, line);) {
        stringstream lineStream(line);
        vi coords;
        int coord;
        while (lineStream >> coord) {
            coords.push_back(coord);
        }
        for (auto item : coords) {
            cout << item << " ";
        }
        if (sz(coords) == 3 && validateTriangle(coords)) {
            cout << "are the vertices of a triangle\n";
        } else if (sz(coords) == 4 && validateParallelogram(coords)) {
            cout << "are the vertices of a parallelogram\n";
        } else if (sz(coords) == 6 && validateHexagon(coords)) {
            cout << "are the vertices of a hexagon\n";
        } else {
            cout << "are not the vertices of an acceptable figure\n";
        }
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



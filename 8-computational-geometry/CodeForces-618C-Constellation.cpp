#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef long long ll;
typedef std::pair<int,int> pii;
typedef std::pair<ll,ll> pll;
typedef pair<double, double> pt;

constexpr int N = 1e6 + 10;
const double EPS = 1e-8;

int n;
vector<pair<pt, int>> p(N);

pt operator-(pt a, pt b) {
  return pt(a.x - b.x, a.y - b.y);
}

bool zero(double x) {
  return fabs(x) <= EPS;
}

double cross(pt a, pt b) {
  return a.x*b.y - a.y*b.x;
}


bool cw(pt a, pt b, pt c) {
  return cross(b - a, c - a) < 0;
}

// true if left or straight
// sometimes useful to instead return an int
// -1, 0 or 1: the sign of the cross product
bool ccw(pt a, pt b, pt c) {
  return cross(b - a, c - a) > 0;
}

bool straight(pt a, pt b, pt c) {
  return cross(b - a, c - a) == 0;
}

signed main() {
    // READING INPUT
    cin >> n;
    for (int i = 0; i < n; ++i) {
        ll x, y; cin >> x >> y;
        p[i] = {{x, y}, i + 1};
    }

    // COMPUTATION

    sort(p.begin(), p.begin() + n, [](const pair<pt, int>& a, const pair<pt, int>& b) {
        if (a.first.x != b.first.x) {
            return a.first.x < b.first.x;
        }
        return fabs(a.first.y) < fabs(b.first.y);
    });

    for (int i = 0; i + 2 < n; ++i) {
        if (!straight(p[i].first, p[i+1].first, p[i+2].first)) {
            cout << p[i].second << " " << p[i + 1].second << " " << p[i + 2].second;
            return 0;
        }
    }

    return 0;
}

// should be simple,
// choose any non-flat line as the first triangle
// then iterate through all the points, checking if it is inside our triangle
// if so, replace onr of the edges of the triangle.

// to check if something is in a triangle, define triangle ABC and point P
// AB X AP, BC X BP, CA X CP - all must be the same sign.


// BETTER WAY TO DO THIS:
// sort by x value, find the first three points that aren't collinear!
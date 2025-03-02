#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef long long ll;
typedef std::pair<int,int> pii;
typedef std::pair<ll,ll> pll;
typedef pair<double, double> pt;

constexpr int N = 1e6;
constexpr int M = 3 * 1e3 + 100;
constexpr int Q = 1e6 + 1000;
const double EPS = 1e-8;

int n,m;
vector<pair<pt, bool>> points;
vector<pair<pt, bool>> ch(N);

pt operator-(pt a, pt b) {
  return pt(a.x - b.x, a.y - b.y);
}

bool zero(double x) {
  return fabs(x) <= EPS;
}

double cross(pt a, pt b) {
  return a.x*b.y - a.y*b.x;
}

bool ccw(pt a, pt b, pt c) {
  return cross(b - a, c - a) > 0;
}

vector<pair<pt, bool>> half_hull(vector<pair<pt, bool>> pts) {
  vector<pair<pt, bool>> res;
  for (int i = 0; i < pts.size(); i++) {
    // ccw means we have a left turn; we don't want that
    while (res.size() >= 2 &&
           ccw(pts[i].first, res[res.size()-1].first, res[res.size()-2].first)) {
            // we also want to keep the values that lie on the same line as the hull
            // and not pop them off - so need to edit ccw function to not return true on striaghts
      res.pop_back();
    }
    res.push_back(pts[i]);
  }
  return res;
}


vector<pair<pt, bool>> convex_hull(vector<pair<pt, bool>> pts) {
    sort(pts.begin(), pts.end(), [](const pair<pt, bool>& a, const pair<pt, bool>& b) {
        return a.first < b.first; 
    });
    vector<pair<pt, bool>> top = half_hull(pts);

    reverse(pts.begin(), pts.end());
    vector<pair<pt, bool>> bottom = half_hull(pts);

    top.pop_back();
    bottom.pop_back();
    vector<pair<pt, bool>> res(top.begin(), top.end());
    res.insert(res.end(), bottom.begin(), bottom.end());
    return res;
}

signed main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        ll x, y; cin >> x >> y;
        points.emplace_back(make_pair(x, y), false);
    }

    cin >> m;
    for (int i = 0; i < m; ++i) {
        ll x, y; cin >> x >> y;
        points.emplace_back(make_pair(x, y), true);
    }

    ch = convex_hull(points);

    for (auto p : ch) {
        if (p.second == true) {
            std::cout << "NO\n";
            return 0;
        }
    }
    std::cout << "YES\n";

    return 0;
}
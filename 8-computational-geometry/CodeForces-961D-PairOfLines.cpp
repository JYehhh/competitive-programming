#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef long long ll;
typedef std::pair<int,int> pii;
typedef std::pair<ll,ll> pt;
// typedef pair<double, double> pt;

constexpr int N = 1e5 + 10;
const double EPS = 1e-8;

int n;
vector<pt> p(N);

pt operator-(pt a, pt b) {
  return pt(a.x - b.x, a.y - b.y);
}


ll cross(pt a, pt b) {
  return a.x*b.y - a.y*b.x;
}

bool cw(pt a, pt b, pt c) {
  return cross(b - a, c - a) < 0;
}

bool zero(double x) {
  return fabs(x) <= EPS;
}

bool ccw(pt a, pt b, pt c) {
  return cross(b - a, c - a) > 0;
}

bool straight(pt a, pt b, pt c) {
  return zero(cross(b - a, c - a));
}


bool check(pt l1, pt l2) {
    bool seen[N] = {false};;
    int sc = 0;
    
    // no need to preset seen, will be set correctly after first pass
    for (int i = 0; i < n; ++i)
        if (straight(l1, l2, p[i])) {
            seen[i] = true;
            sc++;
        }
            
    // find a point 
    pt p1, p2;
    int lf = 0;
    for (int i = 0; i < n; ++i) {
        if (seen[i]) continue;
        if (lf == 0) {
            p1 = p[i];
            lf++;
        } else if (lf == 1) {
            p2 = p[i];
            lf++;
        } else {
            if (!straight(p1, p2, p[i])) return false;
        }
    }

    return true;
}

signed main() {
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        p[i] = {x, y};
    }

    if (n <= 3) {
        cout << "YES\n"; return 0;
    }

    // don't actually need to find a third base
    // cout << check(p[0], p[1]) << "\n";
    // cout << check(p[0], p[2]) << "\n";
    // cout << check(p[1], p[2]) << "\n";

    if (check(p[0], p[1]) || check (p[1], p[2]) || check (p[0], p[2])) cout << "YES\n";
    else cout << "NO\n";
    
    return 0;
}

// if there are three or less points, the answer is YES
// otherwise, choose 3 non-collinear points
    // they should make three lines.
        // for each of the lines, erase every other point that line - and then check
        // if every other point forms one line
    // if that fails, try it with the next line - try all three lines, if fail, then fail
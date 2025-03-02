#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef long long ll;
typedef std::pair<int,int> pii;
typedef std::pair<ll,ll> pll;
typedef pair<int, int> pt;

constexpr int N = 1e2 + 100;
constexpr int M = 3 * 1e3 + 100;
constexpr int Q = 1e6 + 1000;
const double EPS = 1e-8;

pt operator-(pt a, pt b) {
  return pt(a.x - b.x, a.y - b.y);
}

int cross(pt a, pt b) {
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

bool on_line(pt a, pt b, pt c) {
  return zero(cross(b - a, c - a));
}

int n, m, q;
vector<pt> r(N);
vector<pt> b(M);
vector<int> res;
int bur[N][N];
int blacksUnderRed[N]; // keeps track of the number of blacks directly under the red point >= 
int blacksUnderRedStrict[N]; // > Y

void precompute() {
    for (int i = 1; i <= n; i++) {
        for (int l = 1; l <= m; ++l) {
            // if red.x == black.x
            if (r[i].x == b[l].x && r[i].y >= b[l].y) {
                blacksUnderRed[i]++;
            }

            if (r[i].x == b[l].x && r[i].y > b[l].y) {
                blacksUnderRedStrict[i]++;
            }
        }
    }


    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int count = 0;
            // skip if we're at the same point
            if (i == j) continue;
            // skip if the y values are the same
            if (r[i].x == r[j].x) continue;

            if (r[i].x < r[j].x) { // left to right - positive
                // FROM LEFT TO RIGHT, needs to be STRICTLY UNDER
                for (int l = 1; l <= m; ++l) {
                    auto bp = b[l];
                    bool betw = bp.x > r[i].x && bp.x < r[j].x; // (L, R)
                    bool under = cw(r[i], r[j], bp);
                    bool on = on_line(r[i], r[j], bp);
                    if (betw && under) count++;
                }
            } 
            
            else { // right to left - negative
                // FROM RIGHT TO LEFT, this is subtract, so it can be on the line
                for (int l = 1; l <= m; ++l) {
                    auto bp = b[l];
                    bool betw = bp.x < r[i].x && bp.x > r[j].x; // (L, R)
                    bool under = ccw(r[i], r[j], bp);
                    if (betw && under) count--;
                }
            }

            bur[i][j] = count;
        }
    }
}

signed main() {
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        int x, y; cin >> x >> y;
        r[i] = {x, y};
    }
    for (int i = 1; i <= m; ++i) {
        int x, y; cin >> x >> y;
        b[i] = {x, y};
    }
    
    // precompute black dots under every red pair
    precompute();

    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= n; ++j) {
    //         std::cout << bur[i][j] << " ";
    //     }
    //     std::cout << "\n";
    // }
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int k; cin >> k;
        vector<int> poly(k);

        int maxX = -1e5;
        int minX = 1e5;
        for (int j = 0; j < k; ++j) {
            cin >> poly[j];
            
            maxX = max(maxX, r[poly[j]].x);
            minX = min(minX, r[poly[j]].x);
        }

        int cb = 0;
        for (int j = 0; j < k; ++j) {
            int start = poly[j];
            int end = poly[(j+1)%k];
            int prev = poly[(((j - 1) % k) + k) % k];
            int augment = bur[start][end];
            cb += augment;

            // is vertical line
            if (r[start].x == r[end].x) {
                
                // check if going left to right
                // cannot have 3 colinear points

                // left to right
                if (r[prev].x < r[start].x) {
                    // strict delete the start
                    cb -= blacksUnderRedStrict[start];

                    // strict add the end
                    cb += blacksUnderRedStrict[end];
                }

                // right to left
                else if (r[prev].x > r[start].x) {
                    // soft add the start
                    cb += blacksUnderRed[start];

                    // soft delete the end
                    cb -= blacksUnderRed[end];
                }
            }

            // IE going from left to right
            // when adding: strict
            if (r[start].x < r[end].x && r[end].x != maxX) {
                cb += blacksUnderRedStrict[end];
            }

            // IE going from right to left
            if (r[start].x > r[end].x && r[end].x != minX) {
                cb -= blacksUnderRed[end];
            }
        }

        res.push_back(cb);
    }

    for (auto i : res) 
        cout << i << "\n";
}

// For this question, we can use the trapezoidal rule
// precompute all the black dots below every red line pair
// when a query comes through, we can use it to compute how many inside the

// y value will go below 0 sometimes, just move them to all be above 0, store a shift valu
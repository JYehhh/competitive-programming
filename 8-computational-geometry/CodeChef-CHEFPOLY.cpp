#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

const int VERTICAL = 0;
const int RIGHT = 1;
const int LEFT = 2;


typedef long long ll;
typedef std::pair<int,int> pii;
typedef std::pair<ll,ll> pt;
// typedef pair<double, double> pt;

constexpr int N = 1e2 + 100;
constexpr int M = 3 * 1e3 + 100;
constexpr int Q = 1e6 + 1000;
const double EPS = 1e-8;

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

bool on_line(pt a, pt b, pt c) {
  return cross(b - a, c - a) == 0;
}

int determine_direction(pt start, pt end) {
    if (start.x < end.x) return RIGHT;
    else if (start.x > end.x) return LEFT;
    else return VERTICAL;
}

int n, m, q;
vector<pt> r(N);
vector<int> ur_strict(N);
vector<int> ur(N);
vector<pt> b(M);
vector<int> res;
int bur[N][N];

void precompute() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int count = 0;
            // skip if we're at the same point
            if (i == j) continue;
            // skip if the x values are the same
            if (r[i].x == r[j].x) continue;

            if (r[i].x < r[j].x) { // left to right - positive
                // FROM LEFT TO RIGHT, needs to be STRICTLY UNDER
                for (int l = 1; l <= m; ++l) {
                    auto bp = b[l];
                    bool betw = bp.x > r[i].x && bp.x < r[j].x;
                    bool under = cw(r[i], r[j], bp);
                    if (betw && under) count++;
                }
            } 
            
            else { // right to left - negative
                // FROM RIGHT TO LEFT, this is subtract, so it can be on the line
                for (int l = 1; l <= m; ++l) {
                    auto bp = b[l];
                    bool betw = bp.x < r[i].x && bp.x > r[j].x;
                    bool under = ccw(r[i], r[j], bp);
                    bool on = on_line(r[i], r[j], bp);
                    if (betw && (under || on)) count--;
                }
            }

            bur[i][j] = count;
        }
    }

    // precompute a count for every red
    for (int i = 1; i <= n; ++i) {
        for (int l = 1; l <= m; ++l) {
            if (b[l].x == r[i].x && b[l].y < r[i].y) ur_strict[i]++;
            if (b[l].x == r[i].x && b[l].y <= r[i].y) ur[i]++;
        }
    }
}

int get_leftmost(vector<int>& indices) {
    int leftmost = INT_MAX;
    for (int idx : indices) {
        leftmost = min(leftmost, (int)r[idx].x);
    }
    return leftmost;
}

int get_rightmost(vector<int>& indices) {
    int rightmost = INT_MIN;
    for (int idx : indices) {
        rightmost = max(rightmost, (int)r[idx].x);
    }
    return rightmost;
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
    while(q--) {
        ll k; cin >> k;
        vector<int> poly(k);
        for (int j = 0; j < k; ++j) cin >> poly[j];

        int lm = get_leftmost(poly);
        int rm = get_rightmost(poly);
        
        int cb = 0;
        for (int j = 0; j < k; ++j) {
            int start = poly[j];
            int end = poly[(j+1)%k];
            int prev = poly[(((j-1)%k)+k)%k];

            int dir = determine_direction(r[start], r[end]);

            int black_under_red = bur[start][end];
            cb += black_under_red;

            // compute the previous direction
            // CHECK IF IT'S A VERTICAL LINE and not at the rightmost or leftmost
            if (dir == VERTICAL) {
                // get direction from the previous value
                dir = determine_direction(r[prev], r[start]);
                if (dir == RIGHT) {
                    cb -= ur_strict[start];
                    cb += ur_strict[end];
                }
                
                else if (dir == LEFT) {
                    cb += ur[start];
                    cb -= ur[end];
                } 
                
                else {
                    cerr << "should be no three collinear lines!\n";
                    return 1;
                }
            }
            

            // if (black_under_red == 0) continue; // !! START FIXING

            // if it's a vertical line: determine direction based on previous's sign
            // check if the bur from previous to start is negative or positive - it will never be 0
            // j = 0, start will be j = k-1
            // is j - 1 % k = k - 1???? 

            

            // if it's not a vertical line: determine direction based on signage
            else if (dir == RIGHT) { // going to the right
                if (r[end].x != rm) cb += ur_strict[end];
                // include the right point if we're not at the rightmost
            } else if (dir == LEFT) { // going to the left
                if (r[end].x != lm) cb -= ur[end];
                // include the left point if we're not at the leftmost
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

// y value will go below 0 sometimes, just move them to all be above 0, store a shift value
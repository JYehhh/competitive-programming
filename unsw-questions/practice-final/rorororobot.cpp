#include <bits/stdc++.h>

using ll = long long;
typedef std::pair<int,int> pii;

using namespace std;

constexpr int INF = 1e9;

// Bounds
ll N = 1e10;
ll M = 1e6;

// Variables
int n, m, q;
vector<int> bcc(M);


signed main() {
    // rows are 1-n bot to top
    // cols are 1-m left to right

    // it will move up down, left or right, all k times

    // this is shortest path / network flow...
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i) std::cin >> bcc[i];
    std::cin >> q;
    
    for (int i = 0; i < q; ++i) {
        int xs, ys, xf, yf, k;
        std::cin >> xs >> ys >> xf >> yf >> k;
        
        set <pii> seen;
        std::queue<pii> que;

        que.emplace(ys, xs);
        while (!que.empty()) {
            pii cur = que.front(); que.pop();
            int y = cur.first, x = cur.second;
            pii c(y, x);
            if (seen.count(c)) continue;
            seen.insert(c);

            // consider all possible next positions
            // check if they hit a boundary first
            bool can_up = (y + k <= n);
            bool can_down = (y - k >= 1);
            bool can_left = (x - k >= 1);
            bool can_right = (x + k <= m);

            // now check if they land or pass a blocked cell
            can_up = can_up;
            can_down = can_down && (y - k > bcc[x]);
            if (can_left)
                for (int j = 1; j <= k; ++j) if (y <= bcc[x - j]) can_left = false;
            if (can_right)
                for (int j = 1; j <= k; ++j) if (y <= bcc[x + j]) can_right = false;

            if (can_up) que.emplace(y + k, x);
            if (can_down) que.emplace(y - k, x);
            if (can_left) que.emplace(y, x - k);
            if (can_right) que.emplace(y, x + k);
        }
        if (seen) std::cout << "YES\n";
        else std::cout << "NO\n";

    }

    // feels like shortest path - just bfs from the source
    // check the path, if it crosses over a blocked cell, break
    // if it goes out of bounds, break

    // check at the end of the test case if there is a pth to the end.

}
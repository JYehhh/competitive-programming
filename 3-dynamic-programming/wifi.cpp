#include <bits/stdc++.h>
#include <cassert>

using ll = long long;

const int N = 100100;
const ll INF = 1e18;

int n, k;
std::string s;
// ll dp[N];
std::vector<ll> dp;

int main() {
    std::cin >> n >> k;
    std::cin >> s;

    assert(s.size() == n);

    // for (int i = 0; i <= n; ++i) update(i, INF);

    // range tree will store cost of turning on each router
    // dp[i] will store cost of turning on every element.
        // can either inherit a router cost in range
        // or turn itself on if nothing is in range.

    dp.push_back(0);

    std::queue<ll> r;
    for (int i = 1; i <= n; ++i) {
        if (s[i - 1] == '1') r.push(i);
    }

    

    for (int i = 1; i <= n; ++i) {
        // for every element, check all the routers that COULD cover it, 
        while (!r.empty() && r.front() < i - k) r.pop();
        // now, the front element in the queue is the closest router that is in range (cghecking lower bound)
        if (!r.empty() && r.front() < i+k) { // if the element in the queue can cover it (checking upper bound)
            int lb = std::max(ll(0), r.front() - k - 1);
            dp.push_back(std::min(dp[i-1] + i, dp[lb] + r.front()));
        } else {
            dp.push_back(dp[i-1]+i);
        }
    }
    std::cout << dp[n] << std::endl;
}




// // RANGE TREE STUFF
// ll tree[1<<18]; // range min tree with point update
// // instead of explicitly storing each node's range of responsibility [cL,cR), we calculate it on the way down
// ll query(ll qL, ll qR, int i = 1, int cL = 0, int cR = n) {
//   if (cL == qL && cR == qR)
//     return tree[i];
//   ll mid = (cL + cR) / 2;
//   ll ans = INT_MAX;
//   if (qL < mid) ans = std::min(ans, query(qL, std::min(qR, mid), i * 2, cL, mid));
//   if (qR > mid) ans = std::min(ans, query(std::max(qL, mid), qR, i * 2 + 1, mid, cR));
//   return ans;
// }


// void update(ll p, ll v, ll i = 1, ll cL = 0, ll cR = n) {
//   if (cR - cL == 1) {
//     tree[i] = v;
//     return;
//   }
//   ll mid = (cL + cR) / 2;
//   if (p < mid)
//     update(p, v, i * 2, cL, mid);
//   else
//     update(p, v, i * 2 + 1, mid, cR);
//   tree[i] = std::min(tree[i*2],tree[i*2+1]);
// }


// Router
    // On - Min between:
        // inheriting off cost of on end of range
        // inheriting on cost of last router within range
    // Off - Min between: 
        // INF if there is no router within range
        // inheriting on cost of last router within range
// Not Router
    // On - Min between:
        // inheriting on cost of element before it
    // Off - Min between:
        // INF if there is no router within range
        // inheriting on cost of last router within range



// int main() {
//     std::cin >> n >> k;
//     std::cin >> s;

//     assert(s.size() == n);

//     // the range tree will store costs of all routers so we can backtrack.
//     for (int i = 0; i <= n; ++i) {
//         update(i, INF);
//         dp[i][1] = INF;
//         dp[i][0] = INF;
//     }

//     // dp[0] is out of bounds
//     // dp[1] is cost of the first element
//     // dp[n] is last element
//     // same with range tree...

//     // populate base case
//     dp[1][1] = 1;
//     if (s[0] == '1') update(1, dp[1][1]);

//     dp[0][0] = 0;
//     dp[0][1] = 0;

//     for (int i = 2; i <= n; ++i) {
//         int lb = i - k - 1 < 1 ? 0 : i - k - 1;
//         ll lrc = query(lb + 1, i);

//         if (s[i - 1] == '1') { // Router
//             dp[i][1] = std::min(dp[lb][1], lrc) + i;
//             dp[i][0] = lrc;
//             update(i, dp[i][1]);
//         } else { // Not Router
//             dp[i][1] = std::min(dp[i - 1][1], dp[i - 1][0]) + i;
//             dp[i][0] = lrc;
//         }
//     }

//     // pull out final answer
//     std::cout << "0: ";
//     for (int i = 1; i <= n ; ++i) {
//         std::cout << dp[i][0] << " ";
//     }
//     std::cout << std::endl;

//     // std::cout << "1: ";
//     // for (int i = 1; i <= n ; ++i) {
//     //     std::cout << dp[i][1] << " ";
//     // }
//     // std::cout << std::endl << std::endl;


//     std::cout << std::min(dp[n][1], dp[n][0]);

//     return 0;
// }



// int main() {
//     std::cin >> n >> k;
//     std::cin >> s;

//     assert(s.size() == n);

//     // the range tree will store costs of all routers so we can backtrack.
//     for (int i = 0; i <= n; ++i) {
//         update(i, INF);
//         dp[i][1] = INF;
//         dp[i][0] = INF;
//     }

//     // populate base case
    
//     dp[0][0] = 0;
//     dp[0][1] = 0;
//     // std::cout << "processing: 1" << std::endl;
//     // std::cout << "dp[1] = 1" << std::endl << std::endl;

//     dp[1][1] = 1;

//     // perform recurrence
//     for (int i = 2; i < n; ++i) {
//         // std::cout << "processing: " << i << std::endl;
//         int lb = i-k > 1 ? i-k : 0;
//         if (s[i - 1] == '1') { // IF IT'S A ROUTER
//             // std::cout << "considering between " << dp[lb] << " + " << i << " and " << query(lb,i) << std::endl;
//             // check if theres a switched on router near by
            
//             // UPDATE IF YOU DON'T TURN IT ON
//                 // check if theres a switched on router near by
//                 // 
//             dp[i][0] = std::min(dp[lb][0], query(lb,i));

//             // IF YOU DO TURN IT ON
//                 // add it to the list of turned on routers
//                 // populate with cost of 
//             dp[i][1] = std::min(dp[lb][1] + i, query(lb,i));
//             if (dp[lb][1] + i < query(lb,i)) {
//                 // std::cout << "updating 1's tree..." << std::endl;
//                 update(i, dp[i][1]);
//             }
            
//         } else {
//             // IF YOU DON'T TURN IT ON
//             dp[i][] = std::min(dp[i-1][] + i, query(lb,i));
//             // IF YOU DO TURN IT ON
//             dp[i][] = std::min(dp[i-1][] + i, query(lb,i));
//         }
//         // std::cout << "dp[" << i << "] = " << dp[i] << std::endl << std::endl;
//     }

//     for (int i = 1; i < n ; ++i) {
//         std::cout << dp[i][] << " ";
//     }

//     std::cout << std::endl;
//     // pull out final answer
//     std::cout << std::min(dp[n][1], dp[n][0]);

//     // TODO:
//     // am I using query right with inclusive and exclusive bounds
//     // when it hits the lower bound, query should return 0


//     return 0;
// }

// Check if there is a router within K.

// Router
    // On - Min between:
        // inheriting off cost of on end of range
        // inheriting on cost of last router within range
    // Off - Min between: 
        // INF if there is no router within range
        // inheriting on cost of last router within range
// Not Router
    // On - Min between:
        // inheriting on cost of element before it
    // Off - Min between:
        // INF if there is no router within range
        // inheriting on cost of last router within range





// std::vector<std::pair<int, ll>> segments[N]; // (start, cost)


// void update(int p, ll v, int i = 1, int cL = 0, int cR = n);
// ll query(int qL, int qR, int i = 1, int cL = 0, int cR = n); // [qL, qR)



// int main() {
//     std::cin >> n >> m;
//     for (int i = 0; i < m; i++) {
//         int s, e, c;
//         std::cin >> s >> e >> c;
//         segments[e].emplace_back(s, c); // preprocess: collate by end point
//     }

//     for (int i = 0; i <= n; i++)
//         update(i,INF);

//     for (int i = 0; i <= n; i++) {
//         dp[i] = INF;
//         for (auto seg : segments[i]) {
//             ll prevcost = seg.first == 0 ? 0 : query(seg.first-1, i);
//             dp[i] = std::min(dp[i], prevcost + seg.second);
//         }
//         update(i, dp[i]);
//     }
//     std::cout << dp[n] << '\n';
// }

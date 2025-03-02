#include <bits/stdc++.h>

using ll = long long;

constexpr int N = 20;

int n, m, k;
ll dp[N][1<<N];
int b[N][N];
int a[N];

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    std::cin >> n >> m >> k;

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    for (int i = 0; i < k; ++i) {
        int x, y;
        std::cin >> x >> y;
        std::cin >> b[x-1][y-1]; // the x and y are 1 based indexing, move it to 0
    }

    // populate base case
    // for every meal i, the benefit of eating only that meal is a[i] 
    for (int i = 0; i < n; ++i) { // maybe i <= n?
        dp[i][1<<i] = a[i];
    }

    for (int s = 0; s < (1<<n); s++) { // for all subsets of n elements in increasing order
        if (__builtin_popcount(s) <= m) { // run bottom up from all subsets less than or equal to m (smallest to largest)
            // iterate through the dishes that are on
            for (int i = 0; i < n; ++i) {
                if (s & (1 << i)) { // if the i'th bit is turned on
                    // iterate through all j bits
                    for (int j = 0; j < n; ++j) {
                        if (s & (1 << j)) {
                            if (j != i) dp[i][s] = std::max(dp[i][s], dp[j][s ^ (1 << i)] + a[i] + b[j][i]);
                        }
                    }
                }
            }
            // s = 000101101010
            // iterate through the values 1, 3, 5, 6, 8
            // find all pairs where i, j are not the same
            // we need to be able to iterate through all the switched on values in the set and which
        }

        // iterate through every element in the set
  
    }

    ll ans = 0;

    for (int s = 0; s < (1<<n); s++) {
        if (__builtin_popcount(s) == m) {
            for (int i = 0; i < n; ++i) {
                ans = std::max(dp[i][s], ans);
            }
            
        }
        
    }

    std::cout << ans;

    // OTHER NOTES FOR REVISION LATE
    // for each subset, populate cache with each element as the end point

    // recurrence is: dp[i][S] = max(dp[i][S], dp[j][S'] + b[i][j] + b[i])
        // where S is every possible subset of size less than or equal to m
        // S' is the set without meal i
        // where i and j are in S

    // once populated, find max of all dp's where S is of size m

    return 0;
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = 1e18; // Large number to represent "infinity"

int main() {
    int n, k;
    string s;
    cin >> n >> k >> s;

    vector<ll> dp(n + 1, INF);  // dp[i] represents the minimum cost to connect all rooms up to room i
    dp[0] = 0;  // Base case: cost to connect 0 rooms is 0

    // Iterate over all rooms
    for (int i = 1; i <= n; ++i) {
        // Option 1: Connect room i directly
        dp[i] = dp[i - 1] + i;

        // Option 2: Place a router at some room j (where j <= i and s[j-1] == '1')
        for (int j = max(1, i - k); j <= min(n, i + k); ++j) {
            if (s[j - 1] == '1') {
                dp[i] = min(dp[i], dp[max(0, j - k - 1)] + j);
            }
        }
    }

    // The answer is the minimum cost to connect all n rooms
    cout << dp[n] << endl;

    return 0;
}
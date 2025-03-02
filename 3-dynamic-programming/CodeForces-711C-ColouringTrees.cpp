#include <bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr ll INF = 1e18;
constexpr int N = 105; 
constexpr int M = 105; 
constexpr int K = 105;

int n, m, k;
int c[N]; // colours of trees
int p[N][M]; // reading in paint costs
ll dp[N][M][K]; 

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> c[i]; 
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> p[i][j];
        }
    }

    // make everything infinity in the dp table
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            for (int b = 0; b <= k; ++b) {
                dp[i][j][b] = INF;
            }
        }
    }

    // DP STATE IS d(i, j, k), where d is the min cost of colouring i tree with colour j,
    // and with exactly beauty k.

    // state space is max i * j * k

    // set up base cases:
    if (c[1] == 0) { // if the tree is not coloured, we need to 
        // need to colour all of the different base cases for diff colours
        for (int j = 1; j <= m; ++j) {
            dp[1][j][1] = p[1][j];
        }
    } else {
        // if tree is precoloured, cost for colouring this tree is 0
        dp[1][c[1]][1] = 0;
    }

    
    for (int i = 2; i <= n; ++i) { // go through all tree
        for (int j = 1; j <= m; ++j) { // for every colour
            for (int prev_color = 1; prev_color <= m; ++prev_color) { 
                for (int b = 1; b <= k; ++b) { 
                    if (c[i] != 0) { // if the current tree is precoloured
                        if (c[i] == prev_color) { // case for not adding a new beauty group
                            dp[i][c[i]][b] = min(dp[i][c[i]][b], dp[i-1][prev_color][b]);
                        } else {
                            dp[i][c[i]][b] = min(dp[i][c[i]][b], dp[i-1][prev_color][b-1]); // case for adding a new beauty group
                        }
                    } else { // if the current tree is not precoloured, cost of colouring it j
                        if (j == prev_color) { // if it's the same, don't add new beauty
                            dp[i][j][b] = min(dp[i][j][b], dp[i-1][prev_color][b] + p[i][j]);
                        } else { // if it's not the same, add new beauty :D
                            dp[i][j][b] = min(dp[i][j][b], dp[i-1][prev_color][b-1] + p[i][j]);
                        }
                    }
                }
            }
        }
    }

    // search through and find answer for exactly k groups only...
    ll ans = INF;
    for (int j = 1; j <= m; ++j) {
        ans = min(ans, dp[n][j][k]);
    }

    // output
    if (ans == INF) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5000 + 10;
const int MOD = 998244353;

int n, a[N], sum[N], dp[N][N];
int c[N];

ll modpow(ll a, ll b, int m = MOD); // as earlier, but modulo c

ll inv(ll x) {
  return modpow(x, MOD-2, MOD); // Fermat's little theorem
}

int main() {
    dp[0][0] = 1;

    ll n, ans = 0;
    cin >> n;


    for (int i = 1; i <= n; ++i) {
        int card; cin >> card;
        c[card]++; // store the count of all the cards
        dp[0][i] = 1;
    }

    for (int i = 1; i <= n; ++i) {
        ll sum = 0;
        for (int j = 1; j <= n; ++j) { // iterating through all the card numbers
            ll p = dp[i-1][j-1] * c[j] / (n - i + 1);

            // cumulative probability.
            sum = (sum + p) % MOD;
            dp[i][j] = sum;

            // if 
            if (c[j] >= 2) ans = ans + p * (c[j] - 1) / (n-i); 
        }
    }

}
// dp[i][j]: Represents the cumulative probability (or contribution) of reaching step i with the j-th card being the current card.

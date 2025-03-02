#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int N = 5e3 + 10;
const int MOD = 998244353;


ll n, sum[N], p[N][N], csumdp[N][N], inv[N];

int c[N];

ll modmul(ll x, ll y, int m = MOD) {
    return (x * y) % m;
}

ll modadd(ll x, ll y, int m = MOD) {
    return (x + y) % m;
}

ll modpow(ll x, ll n, int m = MOD) {
    if (n== 0) return 1;

    ll a = modpow(x, n/2, m);
    a = a * a % m;
    if (n % 2 == 1) a = a * x % m;
    return a;
}

// ll inv(ll x) {
//   return modpow(x, MOD-2, MOD); // Fermat's little theorem
// }

int main() {
    p[0][0] = 1; csumdp[0][0] = 1; inv[1] = 1;
    // precompute modular inverse
    for (int i = 2; i <= 5e3 + 10; ++i) inv[i] = (MOD-MOD/i) * inv[MOD%i] % MOD;

    ll n, ans = 0;
    cin >> n;

    // csumdp will hold the sum of all 

    for (int i = 1; i <= n; ++i) {
        int card; cin >> card;
        c[card]++; // store the count of all the cards
        p[0][i] = 1; csumdp[0][i] = 1; 
        // base case for prob of choosing 0 elements with last 
        // card num = i = 1
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) { // iterating through all the card numbers
            // dp[i][j] stores the probability of choosing i element such that the last is j
            p[i][j] = modmul(csumdp[i-1][j-1], modmul(c[j], inv[n - i + 1]));

            csumdp[i][j] = modadd(csumdp[i][j-1], p[i][j]);
            // csum will contain sum of choosing i values with card value less than j
            // to be used in next iteration of i
            
            if (c[j] >= 2) ans = modadd(ans, modmul(p[i][j], modmul(c[j] - 1, inv[n-i])));
        }
    }

    std::cout << ans << "\n";

}

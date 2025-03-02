#include <bits/stdc++.h>

using ll = long long;
using ld = long double;

using namespace std;
constexpr int INF = 1e9;
constexpr ll MOD = 1e9 + 7;
typedef std::pair<int,int> pii;
constexpr int N = 1e6;

ll add_mod(ll a, ll j) {
    return (a + j) % MOD;
}

// ll pow_mod(ll b, ll e) {
//     if (e == 0) return 1;

//     ll a = pow_mod(b, e/2);
//     a = a * a % MOD; // repeated squaring up from 1
//     if (e%2 == 1) a = a * b % MOD; // add in the extra element
//     return a;
// }

ll mul_mod(ll a, ll b) {
    return ((a % MOD) * (b % MOD)) % MOD;
}

ll sub_mod(ll a, ll b) {
    return (((a - b) % MOD) + MOD) % MOD;
}

int t;
int p2[N];

signed main() {
    std::cin >> t;

    //precompute all powers of 2
    p2[0] = 1;
    for (int i = 1; i < N; ++i) p2[i] = mul_mod(2, p2[i-1]);

    for (int i = 0; i < t; ++i) {
        int n; std::cin >> n;

        std::vector<ll> s(n);
        for (int j = 0; j < n; ++j) std::cin >> s[j];

        // for all subsets of this set, get max - min, add it to the sum
        // get sum of all max's of all subsets
        ll max_sum = 0;
        std::sort(s.begin(), s.end(), std::greater<ll>());
        for (int j = 0; j < n; ++j) {
            max_sum = add_mod(max_sum, mul_mod(s[j], p2[n-j-1]));
        }

        ll min_sum = 0;
        std::sort(s.begin(), s.end());
        for (int j = 0; j < n; ++j) {
            min_sum = add_mod(min_sum, mul_mod(s[j], p2[n-j-1]));
        }

        std::cout << sub_mod(max_sum, min_sum) << "\n";
    }
    
    return 0;
}
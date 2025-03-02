#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 255;
const ll MOD = 1e9 + 7;
ll n, k;
ll f[N];

ll modadd(ll a, ll b, ll m = MOD) {
    return (a + b) % m;
}

ll modsub(ll a, ll b, ll m = MOD) {
    return ((a - b) % m + m) % m; 
}

ll modmul(ll a, ll b, ll m = MOD) { 
    return (a * b) % MOD; 
}

ll modpow(ll x, ll n, ll m = MOD) {
    if (n == 0) {
        return 1;
    }
    ll a = modpow(x, n / 2);
    a = a * a % m;
    if (n % 2 == 1) {
        a = a * x % m;
    }
    return a;
}


ll inv(ll x) {
  return modpow(x, MOD-2, MOD); // Fermat's little theorem
}

ll modchoose(ll n, ll k, ll m = MOD) {
    ll res = modmul(f[n], inv(f[n-k]));
    return modmul(res, inv(f[k]));
}


void factorials() {
    f[0] = 1;
    for (int i = 1; i < N; ++i) {
        f[i] = (i * f[i-1]) % MOD;
    }
}

signed main() {
    std::cin >> n >> k;
    factorials();

    ll res = modpow(modsub(modpow(k, n), modpow(k-1, n)), n);
    
    for (int i = 1; i < n; i++) {
        ll comb = modchoose(n, i);
        ll arr = modpow(modmul(modpow(k-1, i), modsub(modpow(k, n-i), modpow(k-1, n-i))), n);
        ll invalid = modmul(comb, arr);
        
        if (i % 2 == 0) res = modadd(res, invalid);
        else res = modsub(res, invalid);
    }

    std::cout << res << "\n";

    return 0;
}


// number of ways to allocate n cells with 1 .. k values
// subtract
// number of ways to allocate n cells 

// Number of grids where all columns are valid
// Number of ways a single column can be valid:
// k^n - (k - 1)^n
    // total number of ways to fill all cells in the column with any number
    // - total number of ways to fill all cells in the column with only 2-k
// now the column has at least 1, 1
// since there are N columns: (k ^ n - (k - 1) ^ n) ^ n

// some of those may be invalid, as the rows may be set wrong (i)
// for every single i, there are nCi invalid row combinations

// now we partitiion the column into invalid and valid:
    // INVALID:
    // number of ways to fill i cells excluding 1
    // (k - 1) ^ (i)

    // VALID
    // number of ways to fill n - 1 cells in the column with at least 1 in them
    // ((k) ^ (n - i)) - ((k - 1) ^ (n - i))

// multiply invalid and valid states, and then raise that to the power of the num columns.

// note though, that the valid sections of each column may still form invalid rows
// so what we're computing here really is not the number of ways to fill rows such that
// EXACTLY one row is invalid, it's rather, at LEAST one row is invalid.

// so lets say we subtract the case where at least 1 row is invalid, that would be double counting the arrangements
// where theres two invalid rows (i.e. 2, 1 and 1, 2)
// triple counting the cases where there are 3 invalid rows.

// this is where inclusion exclusion comes in, add and subtract alternatingly.

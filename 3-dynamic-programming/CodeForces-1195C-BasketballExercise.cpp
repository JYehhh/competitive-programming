#include <bits/stdc++.h>

using ll = long long;

constexpr int N = 100000;
ll cache[N][2];
ll input[N][2];

ll f(ll n, ll l) {
    if (cache[n][l] != -1) return cache[n][l];

    if (n == 0) {
        return cache[n][l] = input[n][l];
    } else if (n == 1) {
        if (l == 0) {
            return cache[n][l] = f(n - 1, 1) + input[n][l];
        } else if (l == 1) {
            return cache[n][l] = f(n - 1, 0) + input[n][l];
        }
    }

    if (l == 0) {
        return cache[n][l] = std::max(f(n - 1, 1), f(n - 2, 1)) + input[n][l];
    } else {
        return cache[n][l] = std::max(f(n - 1, 0), f(n - 2, 0)) + input[n][l];
    }
}

int main() {
    ll n;
    std::cin >> n;
    memset(cache, -1, sizeof(cache));

    for (int i = 0; i < n; ++i) {
        std::cin >> input[i][0];
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> input[i][1];
    }

    ll max_end_a = f(n - 1, 0);
    ll max_end_b = f(n - 1, 1);

    ll res = std::max(max_end_a, max_end_b); 
    
    std::cout << res;

    return 0;
}
#include <bits/stdc++.h>

typedef long long ll;

ll n, k;
std::string s, t;

signed main() {
    std::cin >> n >> k;
    // n is length of the string
    // k is the number of strings we can select
    std::cin >> s >> t;

    ll ans = 0;
    ll ns = 1;
    // ns is the number of distinct prefixes up until each step

    for (int i = 0; i < n; ++i) { // iterate through every letter
        int s_bound = s[i] == 'b' ? 1 : 0;
        int t_bound = t[i] == 'a' ? 1 : 0;

        ns = ns * 2 - s_bound - t_bound; 
        // count how many strings we can build up until character i between bounds s and t
        // i.e. iterate through all prefixes of length...

        // since we can only choose up to k strings, we can only have max k prefixes 
        // at a certain point.
        ans += std::min(ns, k);
        ns = std::min(ns, k + 1);         
    }

    std::cout << ans << std::endl;
    
    return 0;
}
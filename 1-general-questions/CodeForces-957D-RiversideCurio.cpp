#include <bits/stdc++.h>

typedef long long ll;

const int N = 1000000;

int n;
int m[N];


int main() {
    std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

    std::cin >> n;

    ll res = 0;

    for (int i = 0; i < n; ++i) std::cin >> m[i];
    
    for (int i = 1; i < n; ++i) { // iterating through number of marks above
        // if the current marks above are less than the marks above from yday
        // some marks went below the wourder
        if (m[i] < m[i-1]) { 
            res += m[i-1] - m[i];  
            m[i] = m[i-1];
        }
        
    }

    for (int i = n - 2; i > 0; --i) {
        if (m[i] + 1 < m[i+1]) {
            res += m[i+1] - m[i] - 1;
            m[i] = m[i+1] - 1;
        }
    }

    std::cout << res << std::endl;
    return 0;
}
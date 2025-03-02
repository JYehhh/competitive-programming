#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
typedef std::pair<int,int> pii;

#define happiness first
#define expiry second


const int N = 1e7;

// struct Compare {
//     bool operator()(pii &a, pii &b) {
//         if (a.expiry == b.expiry) {
//             return a.happiness < b.happiness;
//         }
//         return a.expiry > b.expiry;
//     }
// };

struct Compare {
    bool operator()(pii &a, pii &b) {
        if (a.happiness == b.happiness) {
            return a.expiry > b.expiry; // if happiness is the same, we want the lowest expiry
        }
        return a.happiness < b.happiness;
    }
};

int n;
priority_queue<pii, vector<pii>, Compare> a;

signed main() {
    cin >> n;
    
    for (int i = 0; i < n; ++i) {
        int e, h; cin >> e >> h;
        a.emplace(h,e);
    }

    int cd = 1;
    int happy = 0;

    while (!a.empty()) {
        pii fruit = a.top(); a.pop();

        // cout << fruit.expiry << "\n";
        if (fruit.expiry >= cd) {
            happy += fruit.happiness;
            cd += 1;
        }
    }

    std::cout << happy << "\n";

    // greedy method, choose the one with the lowest expiry date.
    // not always works, because sometimes 
}

// sometimes it's better to forego one of the top items to get a less good item that is about to expire
#include <iostream>
#include <bits/stdc++.h>

using namespace std;


int main() {
    int a, k;

    cin >> a >> k;

    multiset<int> s;
    pair<int, int> activities[a];
    // <end, start>

    for (int i = 0; i < a; ++i) {
        cin >> activities[i].second >> activities[i].first;
    }

    sort(activities, activities + a);

    int count = 0;

    for (int i = 0; i < k; i++) {
        s.insert(0);
    }
    for (auto act : activities) {
        if (s.upper_bound(act.second) != s.begin()) {
            s.erase(prev(s.upper_bound(act.second)));
            s.insert(act.first + 1);
            count++;
        }
    }

    // for (int i = 0; i < a; ++i) {
    //     cout << activities[i].second << " " << activities[i].first << endl;
    // }

    cout << count;

    return 0;
}

#include <iostream>
#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<char, int, less<int>, rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

ordered_set s_count;
stack<char> t;
queue<char> s;
string u;

int main() {
    // collect input
    string string;
    cin >> string;

    // populating s_count
    for (char c : string) {
        if (s_count.find(c) != s_count.end()) { // if c is in set
            ++s_count[c];
        } else {
            s_count[c] = 1;
        }
        s.push(c);
    }

    // iterate through s
    while(!s.empty() || !t.empty()) {
        // if t is empty
        if (t.empty()) {
            t.push(s.front());
            --s_count[s.front()];
            if (s_count[s.front()] == 0) s_count.erase(s.front());
            s.pop();

        } else if (s.empty()) {
            u += t.top();
            t.pop();

        } else {
            // if t is smaller than all elements in S
            if (s_count.order_of_key(t.top()) == 0) {
                u += t.top();
                t.pop();
            } else {
                t.push(s.front());
                --s_count[s.front()];
                if (s_count[s.front()] == 0) s_count.erase(s.front());
                s.pop();
            }
        }
    }

    cout << u;

    return 0;
}
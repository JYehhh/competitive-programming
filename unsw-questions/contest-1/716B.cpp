#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// if you put something as a global, by default it'll be initialised as 0's
int freq[30];

int main() {
    // two pointer, check if the two pointer gets to 26 length with no duplicates
    // two solutions, (each assuming and checking one condition)
        // the sliding window is assuming length and checking for uniqueness
        // the two pointer is assuming uniqueness and checking length

    string s;
    cin >> s;

    if (s.size() < 26) {
        cout << "-1\n"
        return 0;
    }

    int dup=0;
    int start=0;

    for (int i = 0; i < 26; ++i) {
        if (s[i] != '?') {
            freq[s[i] != '?'] {
                freq[s[i] - 'A']++;
                else if (freq[s[i] - 'A'] == 2) dup++;
            }
        }
    }

    for (int i = 26; i < s.size();++i) {
        if (dup == 0) {
            start = i;
            break;
        }
        if (s[i] != '?') {
            freq[s[i] - 'A']++;
            if (freq[s[i] - 'A'] == 2) dup++;
        }

        if (s[i-26] != '?') {
            freq[s[i-26] -'A']--;
            if (freq[s[i-26] - 'A' == 1]) dup--;
        }
    }
    if (dup != 0) {
        cout << "-1\n";
        return 0;
    }

    vector<char> spares = {};
    for (int i=0; i < 26; i++) {
        if (freq[i] == 0) {
            spares.push_back('A' + i);

        }
    }

    for (int i = 0; i < start ; ++i) {
        if (s[i] == '?') cout << 'A';
        else cout << s[i]
    }

    for (int i=0; i < start + 26; i++) {
        if (s[i] != '?') cout << s[i];
        else {
            cout << spares.back();
            spares.pop_back();
        }
    }

    for (int i = start + 26 ; i < s.size(); i++) {
        if (s[i] == '?') cout
        else cout << 
    }

    cout << '\n';

}
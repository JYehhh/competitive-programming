#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int N = 1e5 + 100;
int bugs[N], abil[N], pass[N], pass_i[N], bugs_i[N];
int n, m, s;
int ans[N];

bool able_greater(int i, int j) {
    return abil[i] > abil[j];
}

bool bugs_greater(int i, int j) {
    return bugs[i] > bugs[j]; 
}

bool can_allocate(int len) {
    // checks whether it is possible to assign all the bugs to students in batches of size len
    // we're trying to minimise days, if we're doing it for 2 days, each student can be used twice.

    // SETUP A PRIORITY QUEUE 
    priority_queue<int, vector<int>, greater<int>> pq;
    ll total_passes = 0;

    int cs = 1;
    for (int cb = 1; cb <= m; cb += len) { 
        // iterate through all of the bugs, every time we skip bugs based on num of days.

        // add in all the students that can finish the bug to the priority queue
        while (cs <= n && abil[pass_i[cs]] >= bugs[bugs_i[cb]]) {
            // if we haven't used all students yet, and the ability of the current student 
            // is greater than the complexity of the bug
            pq.push(pass[pass_i[cs]]); 
            ++cs;
        }

        // if no-one can do the bug, return false.
        if (pq.empty()) return false;

        // take the top off of the pq
        total_passes += pq.top(); 
        pq.pop();


        // if we've exceeded the passes, we return false.
        if (total_passes > s) return false;
    }
    return true; 
}

void get_ans(int len) {
    priority_queue<pii, vector<pii>, greater<pii>> pq; 
    int cs = 1;

    for (int cb = 1; cb <= m;) { // iterate through all the bugs
        // add all eligible students for the current bug
        while (cs <= n && abil[pass_i[cs]] >= bugs[bugs_i[cb]]) {
            pq.push(make_pair(pass[pass_i[cs]], pass_i[cs])); 
            ++cs;
        }
        
        // select the least expensive eligible student
        pii le = pq.top(); 
        pq.pop();

        // select that student len times...
        for (int k = 1; k <= len; ++k) {
            if (cb > m) break;

            // allocate the student
            ans[bugs_i[cb]] = le.second; 
            // move the bug along then.
            ++cb;
        }
    }
}

int main() {
    cin >> n >> m >> s;
    
    // READ IN INPUT FOR COMPLEXITY OF BUGS
    for (int i = 1; i <= m; ++i) {
        cin >> bugs[i];
        // storing the original indices of the bugs
        bugs_i[i] = i;
    }

    // READ IN INPUT FOR THE ABILITIES OF STUDENTS
    for (int i = 1; i <= n; ++i) {
        cin >> abil[i];
    }

    // READ IN INPUT FOR THE PASSES
    for (int i = 1; i <= n; ++i) {
        cin >> pass[i];
        // storing the original indices of the passes
        pass_i[i] = i;
    }

    // SORTING
    sort(bugs_i + 1, bugs_i + m + 1, bugs_greater); // sort bugs by difficulty descending
    sort(pass_i + 1, pass_i + n + 1, able_greater); // sort students by ability descending


    // BINARY SEARCH TO FIND SOLUTION
    int l = 1, r = m;
    int res = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (can_allocate(mid)) {
            res = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    if (res == -1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        // calculate result.
        get_ans(res);
        for (int i = 1; i <= m; ++i) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
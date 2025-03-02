#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100000 + 10;

struct student {
    long long requirement;
    long long ability;
    int order;
};

struct bug {
    long long complexity;
    int student;
    int order;
};

int n, m, s;
bug bugs[MAX_N];
student students[MAX_N];
int assignments[MAX_N];  // Final assignments for the bugs

// Comparator for priority_queue (min-heap) to prioritize students by pass requirements
struct CompareStudents {
    bool operator()(const student &a, const student &b) {
        return a.requirement > b.requirement;
    }
};

// Check if it's possible to finish all bugs within 'max_days'
bool can_do(int max_days) {
    priority_queue<student, vector<student>, CompareStudents> pq;  // Min-heap for students
    long long total_passes = 0;
    int i = 1, j = 1;

    // Iterate over bugs
    for (int i = 0; i < m; ) {
        // Add students who can fix this bug (by ability)
        while (j <= n && students[j].ability >= bugs[i].complexity) {
            pq.push(students[j]);
            ++j;
        }

        if (pq.empty()) return false;  // If no student can fix the bug, return false

        // Get the student with the least passes required
        student best_student = pq.top();
        pq.pop();
        
        // Assign this student to the current bug
        for (int k = 0; k < max_days && i < m; ++k, ++i) {
            assignments[bugs[i].order - 1] = best_student.order;
        }

        total_passes += best_student.requirement;  // Track total passes given

        // If passes exceed the limit, return false
        if (total_passes > s) return false;
    }

    return true;
}

int main() {
    cin >> n >> m >> s;

    // Read in the bugs' complexities and initialize their original order
    for (int i = 0; i < m; ++i) {
        cin >> bugs[i].complexity;
        bugs[i].order = i + 1;  // Store original order
    }

    // Read in the students' abilities and pass requirements
    for (int i = 1; i <= n; ++i) cin >> students[i].ability;
    for (int i = 1; i <= n; ++i) {
        cin >> students[i].requirement;
        students[i].order = i;
    }

    // Sort bugs by complexity descending
    sort(bugs, bugs + m, [](bug a, bug b) { return a.complexity > b.complexity; });

    // Sort students by ability ascending
    sort(students + 1, students + n + 1, [](student a, student b) { return a.ability < b.ability; });

    int lo = 1, hi = m, ans = -1;

    // Binary search for the minimum number of days
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (can_do(mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    if (ans == -1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        for (int i = 0; i < m; ++i) {
            cout << assignments[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
#include <bits/stdc++.h>


/*
Variables:
n - number of students
m - number of bugs
s - max number of passes

Algorithm and Approach:
1. Binary search over number of days taken to complete, find the lowest number between 1 and m
2. For each day, compute whether it is possible to finish, and what the order would be. To compute:
    a. Order the bugs descending by date, each bug has to have an original order element.
    b. Allocate the cheapest person that can fix each bug (how to get this?)
    c. If it exceeds the max, then return 0
    d. Up until max days, we repeat the cheapest person that can fix each bug for the next element (how to store repeats)
    e. Reorder bugs based on original order - then read out the student 'order's
*/


using ll = long long;

struct student {
    ll requirement;
    ll ability;
    ll order;
};

struct bug {
    ll complexity;
    ll student;
    ll order;
};


ll n,m,s;

// bool can_do(ll max_days, bug* desc_bugs, student* asc_students) {
//     // In this, we need to iterate across bugs in descending order.
//     std::vector<bool> used(n, false);  // Changed from unordered_set to vector<bool>
//     bug temp_bugs[m];
//     std::copy(desc_bugs, desc_bugs + m, temp_bugs);

//     auto cmp = [](const student &a, const student &b) {
//         return a.requirement > b.requirement;
//     };
//     std::priority_queue<student, std::vector<student>, decltype(cmp)> pq(cmp);

//     ll cur_pass = 0;
//     for (int i = 0; i < m; ++i) {
//         // Add everyone new that can finish the bug into the priority queue
//         student* beg = std::lower_bound(asc_students, asc_students + n, temp_bugs[i].complexity, [](const student &s, ll ability) {
//             return s.ability < ability;
//         });

//         for (auto j = beg; j != asc_students + n; ++j) {  // Lowerbound till end
//             if (!used[j->order - 1]) pq.push(*j);  // Use indexing instead of unordered_set
//         }

//         // If no one can do the bug, return false
//         if (pq.size() == 0) return false;
        
//         student alloc_s = pq.top();
//         cur_pass += alloc_s.requirement;

//         // If this makes us exceed max, return false
//         if (cur_pass > s) return false;

//         // Allocate this bug to the person
//         temp_bugs[i].student = alloc_s.order;

//         // Allocate the next max_days - 1 bugs to the same person
//         for (int j = 0; j < max_days - 1 && i < m - 1; ++j) {
//             ++i;
//             temp_bugs[i].student = alloc_s.order;
//         }

//         pq.pop();
//         used[alloc_s.order - 1] = true;  // Mark the student as used
//     }

//     std::copy(temp_bugs, temp_bugs + m, desc_bugs);
//     return true;
// }

bool can_do(ll max_days, const std::vector<bug>& bugs, const std::vector<student>& students, std::vector<int>& temp_assignments) {
    std::vector<bool> used(n, false);  // Mark students as used
    std::priority_queue<student, std::vector<student>, std::function<bool(const student&, const student&)>> pq([](const student &a, const student &b) {
        return a.requirement > b.requirement;
    });

    ll cur_pass = 0;

    for (int i = 0; i < m; ++i) {
        // Add students who can fix this bug to the priority queue
        auto beg = std::lower_bound(students.begin(), students.end(), bugs[i].complexity, [](const student &s, ll ability) {
            return s.ability < ability;
        });

        for (auto j = beg; j != students.end(); ++j) {  // Lowerbound till end
            if (!used[j->order - 1]) pq.push(*j);  // Use indexing instead of unordered_set
        }

        // If no one can do the bug, return false
        if (pq.empty()) return false;

        // Get the student with the minimum requirement
        student alloc_s = pq.top();
        pq.pop();
        cur_pass += alloc_s.requirement;

        // If this makes us exceed max, return false
        if (cur_pass > s) return false;

        // Directly assign this bug to the student in temp_assignments
        temp_assignments[bugs[i].order - 1] = alloc_s.order;

        // Allocate the next max_days - 1 bugs to the same person
        for (int j = 0; j < max_days - 1 && i < m - 1; ++j) {
            ++i;
            temp_assignments[bugs[i].order - 1] = alloc_s.order;
        }

        used[alloc_s.order - 1] = true;  // Mark the student as used
    }

    return true;
}

int main() {

    std::vector<student> students(n);
    std::vector<bug> bugs(m);
    std::vector<int> assignments(m, -1);      // Store the best (final) assignment
    std::vector<int> temp_assignments(m, -1);  // Temporary assignment for testing

    // Read in bug complexities
    for (int i = 0; i < m; ++i) {
        std::cin >> bugs[i].complexity;
        bugs[i].order = i + 1;
    }

    // Read in student abilities and requirements
    for (int i = 0; i < n; ++i) std::cin >> students[i].ability;
    for (int i = 0; i < n; ++i) {
        std::cin >> students[i].requirement;
        students[i].order = i + 1;
    }

    // Sort bugs by complexity descending
    std::sort(bugs.begin(), bugs.end(), [](bug a, bug b) { return a.complexity > b.complexity; });

    // Sort students by ability ascending
    std::sort(students.begin(), students.end(), [](student a, student b) { return a.ability < b.ability; });

    ll lo = 1;
    ll hi = m;
    ll ans = -1;

    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        // Trying to find the lowest value that is feasible
        // std::cout << "attempting:" << mid << std::endl;
        if (can_do(mid, bugs, students, temp_assignments)) {
            ans = mid;
            assignments = temp_assignments;// store bvalid
            // switch the hi and lo assignments to make it 'highest value' feasible.
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    // Output result
    if (ans == -1) {
        std::cout << "NO";
    } else {
        std::cout << "YES\n";
        for (int i = 0; i < m; ++i) {
            std::cout << assignments[i] << " ";
        }
    }

    return 0;

    // std::sort(bugs, bugs+m, [](bug a, bug b) {
    //     return a.order < b.order;
    // });

    // // std::cout << "finished in: " << ans << " days" << std::endl;

    // // extract possibility, and assignment.
    // if (ans == -1) {
    //     std::cout << "NO";
    //     return 0;
    // } else {
    //     std::cout << "YES\n";
    //     for (auto b : bugs) {
    //         std::cout << b.student << " ";
    //     }
    // }
    
    // return 0;
}
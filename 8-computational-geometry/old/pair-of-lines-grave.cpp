
// bool check(pt l1, pt l2, pt extra) {
//     // PAIRS ARE UNHASHABLE >:(
//     unordered_set<pt> seen = {l1, l2, extra};

//     // loop through every point once
//     for (int i = 0; i < n; ++i) {
//         if (seen.count(p[i])) continue;
//         if (straight(l1, l2, p[i])) seen.insert(p[i]);
//     }

//     int rem = n - seen.size();
//     pt extra_base;
//     if (rem < 2) return true;

//     for (int i = 0; i < n; ++i) {
//         if (seen.count(p[i])) continue;
//         if (n - seen.size() == rem) { // if this is the first one seen
//             extra_base = p[i];
//             continue;
//         } 
//         if (straight(extra, extra_base, p[i])) seen.insert(p[i]);
//     }

//     if (seen.size() == n) return true;
//     return false;
// }


    // // find the first set of 3 non-collinear points
    // bool all_cl = true;
    // p0 = p[0];
    // p1 = p[1];

    // for (int i = 2; i < n; ++i) {
    //     if (!straight(p1, p2, p[i])) {
    //         p2 = p[i];
    //         all_cl = false;
    //     }
    // }

    // if (all_cl) {
    //     cout << "YES\n"; return 0;
    // }

    // // now, for the three lines that the three points create, do our check
    // if (check(p0, p1, p2) || check (p1, p2, p0) || check (p0, p2, p1)) cout << "YES\n";
    // else cout << "NO\n";
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

constexpr int N = 500000 + 100;

// DATA
vector<ll> cities; // 1 indexed, cities are 1 indexed
vector<pair<ll, ll>> roads; // store the initial city connections
stack<pair<ll, ll>> queries; // stores the queries
vector<ll> regions;
map<ll, int> invalid;
priority_queue<ll> maxp;
ll m, q;

// UNION FIND
ll parent[N + 1];
ll subtree_size[N + 1];  

void init(int n) {
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        subtree_size[i] = 1;
    }
}

int root(int x) {
    return parent[x] == x ? x : parent[x] = root(parent[x]);
}

void join(int x, int y) {
    x = root(x); y = root(y);

    if (x == y)
        return;
    
    if (subtree_size[x] < subtree_size[y]) {
        parent[x] = y;
        subtree_size[y] += subtree_size[x];
    } else {
        parent[y] = x;
        subtree_size[x] += subtree_size[y];
    }
}

void connect_regions(int a, int b) {
    // update root region in regions
    int ra = root(a);
    int rb = root(b);
    if (ra == rb) return;
	
    ll pa = regions[ra];
    ll pb = regions[rb];
    ll np = pa + pb;
    join(a, b);
    
    int r = root(a);
    // updates the root region
    regions[r] = np;

    // update priority queue
    // invalidate both old entries
    // cout << "adding to invalid map: " << pa << endl;
    // cout << "adding to invalid map: " << pb << endl;
    invalid[pa]++;
    invalid[pb]++;

    // add in new entry
    maxp.push(regions[r]);

    // if (a == 1 && b == 3) {
    //     // cout << "CONNECTING 1 AND 3 AT THE END GIVES US: " << regions[r] << endl;
    //     // for (int i : regions) {
    //     //     cout << i << " ";
    //     // }
    //     // std::cout << endl;
    // }
}

void update_city (int c, int v) {
    ll diff = v - cities[c];
    cities[c] = v;

    // populate root of region
    int r = root(c);
    ll op = regions[r];
    regions[r] += diff;

    // invalidate region in priority queue
    // cout << "adding to invalid map: " << op << endl;
    invalid[op]++;
    maxp.push(regions[r]);
    
}

signed main() {
    // STEPS
    // 1. Get list of roads post all deletions
    // 2. Store queries in a stack, if the second is -1, then it is 
    ll n;
    std::cin >> n >> m >> q;
    init(n + 1); // +1 to account for the 1 indexed town numbers

    cities.push_back(-1);
    roads.push_back(make_pair(-1,-1)); // to make the roads 1 indexed
    regions.push_back(-1);

    for (int i = 0; i < n; ++i) { // read in populations
        ll p;
        std::cin >> p;
        cities.push_back(p);
        regions.push_back(p);
        maxp.push(p);
    }
    
    for (int i = 0; i < m; ++i) { // read in initial connections
        int a, b;
        std::cin >> a >> b;
        roads.push_back(make_pair(a, b));
    }

    unordered_set<int> d;

    for (int i = 0; i < q; ++i) {
        char qt;
        ll a, b;
        std::cin >> qt;
        
        
        if (qt == 'D') {
            std::cin >> a;
            queries.push(make_pair(a, -1));
            d.insert(a);
        } else if (qt == 'P') {
            std::cin >> a >> b;
            // update the value at city and population
            queries.push(make_pair(a, cities[a]));
            update_city(a, b);
        }
    }

    // for (int i : cities) {
    //     cout << i << " ";
    // }

    // now we can construct the initial roads
    for (int i = 1; i <= m; ++i) { // roads are 1 indexed
        if (d.count(i) != 0) continue;
        connect_regions(roads[i].first, roads[i].second);
    }

    // cout << "beginning " << 1 << " root: " << root(1) << endl;
    // cout << "beginning " << 2 << " root: " << root(2) << endl;
    // cout << "beginning " << 3 << " root: " << root(3) << endl;

    // while (! maxp.empty() ) {
    //     cout << maxp.top() << "\n";
    //     maxp.pop();
    // }
    // return 0
	ll initial_res = -1;

	while(!maxp.empty()) {
		initial_res = maxp.top();
		if (!invalid[initial_res]) break;
		maxp.pop();
		invalid[initial_res]--;
	}

	std::vector<ll> mp;
	if (initial_res != -1) mp.push_back(initial_res);
    

    // iterate through the queries in reverse order as they came
    while (!queries.empty()) { 
        auto qry = queries.top();
        // cout << "query: " << qry.first << " " << qry.second << endl;
        // if (qry.first == 1 && qry.second == -1) {
        //     // find out what we are connecting:
        //     cout << "population of 1: " << cities[1] << endl;
        //     cout << "population of 2: " << cities[2] << endl;
        //     cout << "population of region 1: " << regions[root(1)] << endl;
        //     cout << "population of region 2: " << regions[root(2)] << endl;
        // }
        // cout << "max before: " << maxp.top() << endl;

        if (qry.second == -1) { // this is a D query
            int rn = qry.first;
            connect_regions(roads[rn].first, roads[rn].second);

        // cout << "now " << 1 << " root: " << root(1) << endl;
        // cout << "now " << 2 << " root: " << root(2) << endl;
        // cout << "now " << 3 << " root: " << root(3) << endl;
        } 
        else { // this is a P query
            update_city(qry.first, qry.second);
        }        
        
        ll res;
        while(!maxp.empty()) {
            res = maxp.top();
            if (!invalid[res]) break;
            maxp.pop();
            invalid[res]--;
        }

        // cout << "res: " << res << endl;
        mp.push_back(res);
        queries.pop();
    }
    
    if (!mp.empty()) mp.pop_back();

    for (auto it = mp.rbegin(); it != mp.rend(); ++it) {
        cout << *it << std::endl;
    }

    return 0;
}
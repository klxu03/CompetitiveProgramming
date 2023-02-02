#include <bits/stdc++.h>

using namespace std;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = c - 1; a >= b; a--)
#define isOdd & 1
#define qpow2(exponent) 1 << exponent
/* 2^exponent, because every time shifting bit to the leftBound you are essentially multiplying function by two */
#define max3(a, b, c) max(a, max(b, c))
#define pb push_back
#define f first
#define s second
using ll = long long;

#define mp make_pair
#define t third
#define pll pair<ll, ll>
#define pii pair<int, int>

/* For Debugging Purposes */
#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#else
#define DEBUG(...) 6
#endif

template<typename T, typename S> ostream& operator << (ostream &os, const pair<T, S> &p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename C, typename T = decay<decltype(*begin(declval<C>()))>, typename enable_if<!is_same<C, string>::value>::type* = nullptr>
ostream& operator << (ostream &os, const C &c) {bool f = true; os << "["; for (const auto &x : c) {if (!f) os << ", "; f = false; os << x;} return os << "]";}
template<typename T> void debug(string s, T x) {cerr << "\033[1;35m" << s << "\033[0;32m = \033[33m" << x << "\033[0m\n";}
template<typename T, typename... Args> void debug(string s, T x, Args... args) {for (int i=0, b=0; i<(int)s.size(); i++) if (s[i] == '(' || s[i] == '{') b++; else
if (s[i] == ')' || s[i] == '}') b--; else if (s[i] == ',' && b == 0) {cerr << "\033[1;35m" << s.substr(0, i) << "\033[0;32m = \033[33m" << x << "\033[31m | "; debug(s.substr(s.find_first_not_of(' ', i + 1)), args...); break;}}

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll q, Q, T, k, l, r, x, y, z;
int n, m;

void solve(); 

/* 
Sample:
5
3 10
6 4
1 9
5 8
2 7

Output: 2
*/

// Problem: https://codeforces.com/contest/1503/problem/D 
int main() {
	io;
	ll test_cases = 1;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

bool valid;
vector<array<int, 3>> inp; // {small, big, flip}
vector<pii> left_min; // {min_val (of large), index}
vector<pii> right_max; // {max_val (of large), index}

vector<vector<int>> adj;

vector<vector<int>> comps; // comps[0] is a vector of nodes in that component that need to be bipartite

/* general note, 3rd node has small of 2 as all nodes if valid (not both small) have one each small in that order */

void dfs_comp(vector<int> &comp, int node, vector<bool> &visited) {
    comp.push_back(node);
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (visited[neighbor]) continue;

        dfs_comp(comp, neighbor, visited);
    }
}

void init_comps() {
    vector<bool> visited(n, false);

    f0r(i, n) {
        if (visited[i]) continue;
        vector<int> new_comp;
        dfs_comp(new_comp, i, visited);
        comps.push_back(new_comp);
    }
}

void dfs_color(int node, int prev_color, vector<bool>& visited, int &counter) {
    if (inp[node][2] != prev_color) counter++;
    int new_color = prev_color == 0;
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (visited[neighbor]) continue;
        dfs_color(neighbor, new_color, visited, counter);
    }
}

void solve() {
	cin >> n;
    valid = true;
    inp = vector<array<int, 3>>(n); // {small, big, flip
    // 1 if started flipped so big first, 0 if not flipped}
    adj = vector<vector<int>>(n); // adj for bipartite coloring, + 1 since 1 index

    int inp_f, inp_s;
    f0r(i, n) {
        cin >> inp_f >> inp_s;
        inp_f--; inp_s--; // 0 index
        int swapped = 0;
        if (inp_f > inp_s) {
            swap(inp_f, inp_s);
            swapped = 1;
        }

        if (inp_f > n - 1) valid = false;

        inp[i] = {inp_f, inp_s, swapped};
    }
    sort(inp.begin(), inp.end());

    if (!valid) {
        cout << -1 << endl;
        return;
    }

    left_min = vector<pii>(n); // {min_val (of large), index}
    left_min[0] = {inp[0][1], 0};
    f1r(i, 1, n) {
        left_min[i] = min(left_min[i - 1], {inp[i][1], i});
    }

    right_max = vector<pii>(n); // {max_val (of large), index}
    right_max[n - 1] = {inp[n - 1][1], n - 1};
    r0f(i, n) {
       if (i == n - 1) continue; 
       right_max[i] = max(right_max[i + 1], {inp[i][1], i});
    }

    // form bipartite graphings
    DEBUG(inp);
    DEBUG(left_min);
    DEBUG(right_max);

    // for each node, check if there's a left connection or right connection
    // left meaning new node is smaller than curr node
    // if there is left and right, then add another 2x by getting left_bound and right_bound of range of functional nodes
    f0r(i, n) {
        DEBUG(i);
        int conn = 0; // # of connections
        if (inp[i][1] < right_max[i].first) {
            DEBUG("absolutely smaller", inp[i], right_max[i]);
            // this is absolutely smaller
            conn++;
            adj[i].push_back(right_max[i].second);
            adj[right_max[i].second].push_back(i);

            // bsearch left end and right end
            // left end
            int lo = i + 1; int hi = n;
            while (lo < hi) {
                int mid = lo + (hi - lo)/2;
                if (inp[i][1] > right_max[mid].first) {
                    hi = mid; // go lefter, not even in the cluster of it working yet
                } else if (inp[i][1] < right_max[mid].first) {
                    hi = mid;
                } else {
                    lo = mid + 1;
                }

                DEBUG(lo, hi);
            }
            int left = lo;
            DEBUG(left);
            adj[i].push_back(left);
            adj[left].push_back(i);

            // right end
            lo = i + 1; hi = n;
            while (lo < hi) {
                int mid = lo + (hi - lo)/2;
                if (inp[i][1] > right_max[mid].first) {
                    hi = mid; // go lefter, not even in the cluster of it working yet
                } else if (inp[i][1] < right_max[mid].first) {
                    lo = mid + 1;
                } else {
                    hi = mid;
                }
                DEBUG(lo, hi);
            }
            int right = hi - 1;
            DEBUG(right);
            adj[i].push_back(right);
            adj[right].push_back(i);
            DEBUG("absolutely smaller done");
        }        

        if (inp[i][1] > left_min[i].first) {
            DEBUG("absolutely larger", inp[i], left_min[i]);
            // this is absolutely larger
            conn++;
            adj[i].push_back(left_min[i].second);
            adj[left_min[i].second].push_back(i);

            // bsearch left end and right end
            // left end
            int lo = 0; int hi = i;
            while (lo < hi) {
                int mid = lo + (hi - lo)/2;
                if (inp[i][1] < left_min[mid].first) {
                    lo = mid + 1;
                } else if (inp[i][1] > left_min[mid].first) {
                    hi = mid;
                } else {
                    lo = mid + 1;
                }
            }
            int left = lo;
            DEBUG(left);
            adj[i].push_back(left);
            adj[left].push_back(i);

            // right end
            lo = 0; hi = i;
            while (lo < hi) {
                int mid = lo + (hi - lo)/2;
                if (inp[i][1] < left_min[mid].first) {
                    lo = mid + 1;
                } else if (inp[i][1] > left_min[mid].first) {
                    lo = mid + 1;
                } else {
                    hi = mid;
                }
            }
            int right = hi - 1;
            DEBUG(right);
            adj[i].push_back(right);
            adj[right].push_back(i);
            DEBUG("absolutely larger done");
        }

        if (conn >= 2) valid = false; // depth three
    }
    DEBUG("finished bsearches and creating adj");

    if (!valid) {
        cout << -1 << endl;
        return;
    }

    // now you have adj, let's do the bipartite graph stuff
    // first create the separate components (group them by id) 
    init_comps();
    f0r(i, comps.size()) {
        DEBUG(comps[i]);
    }

    vector<int> non_flipped(comps.size(), 0); //
    vector<bool> visited(n, false);
    // comp[0] is not flipped case
    for (int i = 0; i < comps.size(); i++) {
        vector<int> comp = comps[i];
        // each node in this component is a separate coloring problem
        int counter = 0;
        
        dfs_color(comp[0], 1, visited, counter);
        non_flipped[i] = counter;
    }

    fill(visited.begin(), visited.end(), false);
    // comp[0] is flipped, so one
    for (int i = 0; i < comps.size(); i++) {
        vector<int> comp = comps[i];
        // each node in this component is a separate coloring problem
        int counter = 0;
        
        dfs_color(comp[0], 0, visited, counter);
        if (counter < non_flipped[i]) {
            non_flipped[i] = counter;
        }
    }
    DEBUG(non_flipped);

    int ret = 0;
    f0r(i, non_flipped.size()) {
        ret += non_flipped[i];
    }
    
    cout << ret << endl;
}
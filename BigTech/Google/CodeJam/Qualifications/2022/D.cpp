#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <functional>
#include <array>
#include <deque>
#include <climits>
#include <numeric>

using namespace std;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
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

ll n, m, q, Q, T, k, l, r, x, y, z, g;

class Tree {
    public:
    vector<vector<ll> > edges; // children is just all edges - the parent
    vector<ll> parentArr; // parentArr[1] gives the parent for Node 1
    vector<ll> depth; // depth[1] gives the depth of the current node of Node 1
    vector<ll> size_arr; // Size of subtree including this node as root

    vector<ll> fun;
    vector<ll> special_nodes; // Nodes that have multiple children

    ll running_sum;
    
    Tree(ll nodes) {
        edges = vector<vector<ll> >(nodes);
        parentArr = vector<ll>(nodes);
        depth = vector<ll>(nodes, 0); // Root has depth 0
        size_arr = vector<ll>(nodes);

        fun = vector<ll>(nodes, 0);
        running_sum = 0;

        // Stress testing
        visited = vector<bool>(nodes, false);
    }

    // Basically does a DFS, pre-processing
    ll traverse(ll vertex, ll parentNode = -1) {
        ll size = 1;

        parentArr[vertex] = parentNode;
        // DEBUG(vertex, parentNode);
        for (ll child: edges[vertex]) {
            // We only want to go to childrens and not back up to parent
            if (child != parentNode) { 
                depth[child] = depth[vertex] + 1;
                // This vertex is now the parent, recursively go down
                size += traverse(child, vertex);
            }
        }

        size_arr[vertex] = size;
        return size;
    }

    // Preprocessing similar to BFS
    void preprocess(ll root) {
		deque<ll> dq;
        dq.pb(root);

        while(!dq.empty()) {
            ll current = dq.front();
            dq.pop_front();

            f0r(i, edges[current].size()) {
				ll child = edges[current][i];
                dq.pb(child);
                // DEBUG(current, child);
            }
        }
    }

    void sort_by_depth(vector<ll>& arr) {
        // [this] is C++ capturing so it captures the scope of the variable inside [] so this making it use the instance variables inside this (or this current tree)
        sort(arr.begin(), arr.end(), [this](ll n1, ll n2) {
            return depth_less_than(n1, n2);
        });
    }

    bool depth_less_than(ll n1, ll n2) {
        return depth[n1] > depth[n2];
    }

    // If node has multiple children, select the min one to keep and disown the other children
    void selection(ll node) {
        vector<ll> children_max(edges[node].size()); // children_max[0] is edge[node][0]'s max node in its subtree 
        f0r(i, edges[node].size()) {
            children_max[i] = find_max_node(edges[node][i]);
        }
        DEBUG(children_max);

        ll min_children_fun = LLONG_MAX;
        ll mindex = -1; // min_children_fun_index
        f0r(i, children_max.size()) {
            if (children_max[i] < min_children_fun) {
                min_children_fun = children_max[i];
                mindex = edges[node][i];
            }
        }
        if (mindex == -1) {
            min_children_fun = fun[node];
            mindex = node;
            running_sum += min_children_fun;
        }
        DEBUG(min_children_fun, mindex);

        DEBUG(fun[node], min_children_fun);
        fun[node] = max(fun[node], min_children_fun);

        // Start adding other node maxes to the running sum
        f0r(i, children_max.size()) {
            // if (i != mindex)
            DEBUG(running_sum);
            running_sum += children_max[i];
        }
        DEBUG(running_sum);
        running_sum -= min_children_fun;
        DEBUG(running_sum);

        // break the other childrens so edges[node] is just that one child of mindex
        // edges[node] = {mindex};
        // Actually you're an angry parent so disown all of your children
        edges[node] = {};
    }

    ll find_max_node(ll node) {
        ll currMax = fun[node];
        ll currNode = node;
        while(edges[currNode].size() > 0) {
            DEBUG("find_max_node", fun[edges[currNode][0]], "currMax", currMax);
            currMax = max(currMax, fun[edges[currNode][0]]);
            currNode = edges[currNode][0];
        }
        
        DEBUG("currMax", currMax);
        return currMax;
    }

    // Stress testing
    vector<bool> visited;
    /* Stress testing stuff */
    void activate_initiator(ll node) {
        ll currNode = node;
        ll max_fun = fun[node];
        // DEBUG(fun, visited, running_sum);
        while(currNode != -1 && visited[currNode] == false) {
            visited[currNode] = true;
            max_fun = max(fun[currNode], max_fun);
            currNode = parentArr[currNode];
            // DEBUG(currNode);
        }
        running_sum += max_fun;
    }

    void kill_tree(ll nodes) {
        running_sum = 0;

        // Stress testing
        visited = vector<bool>(nodes, false);
    }
};

ll solve(ll n, vector<ll> &fun, vector<ll> &parents);
// ll solve2(ll n, vector<ll> &fun, vector<ll> &parents);
void solve2();

// Problem: https://codingcompetitions.withgoogle.com/codejam/round/0000000000876ff1/0000000000a45ef7
int main() {
	io;
	ll test_cases = 1;
    cin >> test_cases;
	
	f0r(test_case, test_cases) {
        cout << "Case #" << test_case + 1 << ": ";
		solve2();
	}
}

int main2() {
    ll n = 10;

    // vector<ll> fun = {490, 772, 644, 505, 954, 669, 542, 197, 355, 348};
    // vector<ll> parents = {0, 1, 0, 3, 1, 2, 6, 3, 4, 1};

    // ll sol1 = solve(n, fun, parents);
    // ll sol2 = solve2(n, fun, parents);

    // DEBUG(sol1, sol2);

    f0r(test_case, 10000) {
        DEBUG(test_case);
        vector<ll> fun;
        vector<ll> parents;
        f0r(i, n) {
            ll fun_num = rand() % 1000;
            fun.pb(fun_num);

            ll parent_num = rand() % (i + 1);
            parents.pb(parent_num);
        }

        ll sol1 = solve(n, fun, parents);
        ll sol2 = 69;
        // ll sol2 = solve2(n, fun, parents);
        if (sol1 != sol2) {
            DEBUG("I GOT IT!!!!!!!!!!!!!!!!!!!!!! SOMETHING IS WRONG");
            DEBUG("I GOT IT!!!!!!!!!!!!!!!!!!!!!! SOMETHING IS WRONG");
            DEBUG(fun, parents);
            DEBUG(sol1, sol2);
            break;
        }
    }

}

// Brute solve for stress test
ll solve(ll n, vector<ll> &fun, vector<ll> &parents) {
    // cin >> n;
    Tree t(n);
    t.fun = fun;
    // t.parentArr = parents;

    f0r(i, n) {
        // cin >> t.fun[i];
    }
    // DEBUG(t.fun);

    vector<ll> roots; // List of roots since this is a forest
    f0r(i, n) {
        ll parent = parents[i];
        // cin >> parent;
        parent--;
        if (parent == -1) {
            // I don't need my tree to be bidirectional since index is parent to the child
            // t.edges[i].pb(parent);
            roots.pb(i);
        } else {
            t.edges[parent].pb(i);
        }
    }

    // DEBUG(roots);
    // Do my pre-processing
    f0r(i, roots.size()) {
        t.traverse(roots[i]);
        t.preprocess(roots[i]);
    }

    vector<ll> initiators;
    // DEBUG(t.edges, t.fun, t.parentArr);
    f0r(i, n) {
        if (t.edges[i].size() == 0) {
            initiators.pb(i);
        }
    }
    // DEBUG(initiators);

    vector<ll> a(initiators.size());
    
    ll ret = -1;
    iota(a.begin(), a.end(), 0); // fill a with 0, 1, 2, ..., a.size() - 1
    // DEBUG(a);
    do {
        f0r(i, a.size()) {
            t.activate_initiator(initiators[a[i]]);
            // DEBUG(i);
        }
        ret = max(ret, t.running_sum);
        // DEBUG(ret);
        t.kill_tree(n);
    // do something with a
    } while (next_permutation(a.begin(), a.end()));
    // DEBUG(ret);

    cout << ret << endl;
    return ret;
}

// smart solve
// ll solve2(ll n, vector<ll>& fun, vector<ll>& parents) {
void solve2() {
	cin >> n;
    Tree t(n);
    // t.fun = fun;

    f0r(i, n) {
        cin >> t.fun[i];
    }
    // DEBUG(t.fun);

    vector<ll> roots; // List of roots since this is a forest
    f0r(i, n) {
        ll parent;
        // ll parent = parents[i];
        cin >> parent;
        parent--;
        if (parent == -1) {
            // I don't need my tree to be bidirectional since index is parent to the child
            // t.edges[i].pb(parent);
            roots.pb(i);
        } else {
            t.edges[parent].pb(i);
        }
    }

    // DEBUG(roots);
    // Do my pre-processing
    f0r(i, roots.size()) {
        t.traverse(roots[i]);
        t.preprocess(roots[i]);
    }

    // DEBUG(t.edges, t.parentArr, t.depth);

    f0r(i, n) {
        if (t.edges[i].size() >= 2) {
            t.special_nodes.pb(i);
        }
    }

    // Insert in 0 to special_nodes always
    vector<bool> node_in(n, false);
    // bool is_zero_in = false;
    // f0r(i, t.special_nodes.size()) {
    //     if (t.special_nodes[i] == 0) is_zero_in = true;
    // }
    // if (is_zero_in == false) {
    //     t.special_nodes.pb(0);
    // }
    f0r(i, t.special_nodes.size()) {
        node_in[t.special_nodes[i]] = true;
    }
    f0r(i, roots.size()) {
        if (node_in[roots[i]] == false) {
            t.special_nodes.pb(roots[i]);
        }
    }

    t.sort_by_depth(t.special_nodes);
    DEBUG(t.special_nodes);

    f0r(i, t.special_nodes.size()) {
        DEBUG(t.edges, t.fun);
        t.selection(t.special_nodes[i]);
        DEBUG(t.edges, t.running_sum, t.fun);
    }
    DEBUG(t.running_sum);

    f0r(i, roots.size()) {
        DEBUG("adding root", roots[i]);
        t.running_sum += t.fun[roots[i]];
        DEBUG(t.running_sum);
    }

    DEBUG(t.fun);
    cout << t.running_sum << endl;
    // return t.running_sum;
}
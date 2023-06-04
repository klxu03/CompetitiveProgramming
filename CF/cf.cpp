#include <bits/stdc++.h>

using namespace std;
using ll = long long;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = b; a >= c; a--)
#define pb push_back
#define f first
#define s second

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

/* Variartic Macros and Functions so max(a, b, c, d, ... z) works out of box */
template<typename T> constexpr const inline T& _max(const T& x, const T& y) {return x<y?y:x;}
template<typename T> constexpr const inline T& _min(const T& x, const T& y) {return x<y?x:y;}
template<typename T,typename ...S>constexpr const inline T& _max(const T& m, const S&...s){return _max(m,_max(s...));}
template<typename T,typename ...S>constexpr const inline T& _min(const T& m, const S&...s){return _min(m,_min(s...));}
#define max(...) _max(__VA_ARGS__)
#define min(...) _min(__VA_ARGS__)

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

#include <chrono>
using namespace std::chrono;
struct timer {
    high_resolution_clock::time_point begin;

    timer() {}
    timer(bool b) {
        if (b) start();
    }

    void start() {
        begin = high_resolution_clock::now();
    }

    void print() {
        cout << "Time taken: " << duration_cast<duration<double>>(high_resolution_clock::now() - begin).count() << " seconds" << endl;
    }

    double report() {
        return duration_cast<duration<double>>(high_resolution_clock::now() - begin).count();
    }
};
// Start of main put tin, end of main put tpr (tgt gives you value not printed)
#define tin timer __timer__(1);
#define tpr __timer__.print();
#define tgt __timer__.report()

ll q, Q, T, k, l, r, x, y, z;
int n, m;

void solve();

// Problem URL:
int main() {
    io;
    long long test_cases = 1;
//    cin >> test_cases;

    for (int i = 0; i < test_cases; i++) {
        solve();
    }
}

class UnweightedGraph {
public:
    long long nodes; // # of nodes
    long long edges; // # of edges
    bool undirected;
    vector<vector<int>> parent; // parent of original tree, parent[x] = {y} means x is a parent of y
    vector<int> child; // reverse of parent, child[y] == x

    vector<int> global_c;
    vector<vector<int> > adj; // if adj[0][1] == 3, that means node 0 (2nd connection) must be greater than node 3
    vector<vector<int>> rev_adj;
    vector<int> ans; // the answer, ending return array

    UnweightedGraph() {}

    void init(long long nodes, long long edges, bool undirected) {
        this->nodes = nodes;
        this->edges = edges;
        this->undirected = undirected;

        global_c = vector<int>(nodes);
        ans = vector<int>(nodes, -1);
        parent = vector<vector<int> >(nodes);
        child = vector<int>(nodes, -1);
        adj = vector<vector<int> >(nodes);
        rev_adj = vector<vector<int> >(nodes);
    }

    // check if it's possible based on if each node has a c value <= # of children
    bool handle_possible(int root) {
        vector<int> num_children(n);

        function<void(int)> num_child = [&num_children, this, &num_child](int node) {
            int ret = 0;

            for (int neighbor : this->parent[node]) {
                num_child(neighbor);
                ret += 1 + num_children[neighbor];
            }

//            DEBUG(node, ret);
            num_children[node] = ret;
        };

        num_child(root);

        f0r(i, n) {
            if (global_c[i] > num_children[i]) {
                return false;
            }
        }

        return true;
    }

    void rev_chain_add(int node, vector<int>& c, vector<vector<int>>& rev_chain) {
//        c[node]--;
        int to_dec = c[node] + 1;

        // first decrement everything
        for (int neighbor : rev_chain[node]) {
            c[neighbor] -= to_dec;
        }

        for (int i = 0; i < rev_chain[node].size(); i++) {
            int neighbor = rev_chain[node][i];
            if (neighbor == -1) continue;
            rev_chain_add(neighbor, c, rev_chain);
            rev_chain[node][i] = -1;
        }
    }

    // handle the initial propagation up of the rev_chain. Do not subtract the initial one
    void rev_chain_init(int node, vector<int>& c, vector<vector<int>>& rev_chain) {
        for (int i = 0; i < rev_chain[node].size(); i++) {
            int neighbor = rev_chain[node][i];
            if (neighbor == -1) continue;
            rev_chain_add(neighbor, c, rev_chain);
            rev_chain[node][i] = -1;
        }
    }

    // marking the added array as true for all nodes that are being added to adj from the root
    void chain_add(int node, vector<bool>& added, vector<int> &c, vector<vector<int>>& chain, vector<vector<int>>& rev_chain) {
        added[node] = true;
//        rev_chain_init(node, c, rev_chain);
        rev_chain_add(node, c, rev_chain);
//        DEBUG(node, chain[node], added);
        for (int neighbor : chain[node]) {
//            DEBUG(neighbor);
            if (added[neighbor] == false) {
                chain_add(neighbor, added, c, chain, rev_chain);
            }
        }
    }

    /**
     * handles adding edges to adj from this starting node recursively
     * because this graph is possible to construct, you can just greedy (if 3 is too big, go down its chain until 2)
     *
     * @param node current node we are analyzing
     * @param amt the amount left of children that subroot root must be larger than
     * @param added a vector keeping track of which nodes were already added to adj as this node must be greater than these
     * @param chain chain[x] == {y, z} means that x is directly larger than y and z, along this chain
     * @return the amt we're able to delete from this branch to child down
     */
    int smaller(int node, vector<int>& c, int amt, vector<bool> &added, vector<bool> &visited,vector<vector<int>> &chain, vector<vector<int>> &rev_chain, vector<vector<int>> &local_rev_chain, int root) {
        visited[node] = true;
        int ret = 0;
        // greedily chain add this big chain of children node
        // if not already added and the chain length is smaller than ret
        if (added[node] == false && c[node] + 1 <= amt) {
            // handle this chain delete
            ret += c[node] + 1;
//            DEBUG("chain_add", node);
            chain_add(node, added, c, chain, local_rev_chain);
            rev_chain[node].pb(root);
            chain[root].pb(node);
        }

        for (int neighbor : parent[node]) {
            ret += smaller(neighbor, c, amt - ret, added, visited, chain, rev_chain, local_rev_chain, root);
        }

        return ret;
    }

    // handle the logic for adding adj edges when a node should be bigger than another one
    // eerily similar to a toposort with more
    void get_smaller() {
        vector<int> indegree(n);
        f0r(i, n) {
            if (child[i] != -1) indegree[child[i]]++;
        }
        vector<bool> visited(n);

        deque<int> dq;
        f0r(i, n) {
            if (indegree[i] == 0) {
                dq.pb(i);
            }
        }

        vector<vector<int>> chain(n); // tells the direct neighbor, start of next chain of bigger
        // here chain[2 - 1] would have {3 - 1, 5 - 1} saved from sample
        vector<vector<int>> rev_chain(n); // the reverse of a chain

        while (!dq.empty()) {
            int curr = dq.front();
            dq.pop_front();
            if (visited[curr]) continue;
            visited[curr] = true;

            vector<bool> added(n, false);
            vector<bool> local_visited(n, false);
            vector<int> c = global_c;
            DEBUG(curr);
            vector<vector<int>> local_rev_chain = rev_chain;
            int smaller_res = smaller(curr, c, global_c[curr], added, local_visited, chain, rev_chain, local_rev_chain, curr);
            if (smaller_res != global_c[curr]) {
                cout << "HUGE BRUH" << endl;
                DEBUG(smaller_res, global_c[curr]);
                f0r (i, 5) {
                    DEBUG("=======HUUUUUUUUUUUUUUUUUUUUGEEE ERRRRRROOORRR HERE======");
                }
            }
//            DEBUG(curr, added, local_visited);
            local_visited[curr] = false; // dont want to add a self edge in adj
            vector<int> z = global_c;
            DEBUG(z);
            DEBUG(c);
//            DEBUG(local_visited);

            f0r(i, n) {
                DEBUG(i, curr);
                if (added[i]) {
                    adj[curr].pb(i);
                } else if (local_visited[i]) {
                    // this node is in the subtree of curr, and adj edge was not added
                    // then this node must be greater than curr
                    adj[i].pb(curr);
                }
            }
            DEBUG(curr, adj[curr]);

            DEBUG("===chain===");
            f0r(i, n) {
                DEBUG(i, chain[i]);
            }
            DEBUG("===local_rev_chain");
            f0r(i, n) {
                DEBUG(i, local_rev_chain[i]);
            }
            DEBUG("===adj===");
            f0r(i, n) {
                DEBUG(i, adj[i]);
            }

//            /* shouldn't need to do this since its a fucking tree, toposort on a tree normal parent-child adjacency just means always indegree 0
            if (child[curr] == -1) continue;
            indegree[child[curr]]--;
            if (indegree[child[curr]] == 0) dq.pb(child[curr]);
//             */
//            if (child[curr] != -1) dq.pb(child[curr]);
        }

        DEBUG("===chain===");
        f0r(i, n) {
            DEBUG(i, chain[i]);
        }
    }

    void reverse_adj() {
        f0r(i, n) {
            for (int neighbor : adj[i]) {
                rev_adj[neighbor].pb(i);
            }
        }
    }

    /**
     * The last function, with adj created we know the relationships
     * Which nodes have to be greater than which other nodes
     * We can now do a normal toposort and figure it out (tho weirdly with outdegree since things that this must be greater than other, then this must be processed first)
     */
    void assign_order() {
        vector<int> outdegree(n);
        deque<int> dq;
        f0r(i, n) {
            outdegree[i] = adj[i].size();
            if (outdegree[i] == 0) dq.pb(i);
        }
        reverse_adj();

        int counter = 1;
        while (!dq.empty()) {
            int curr = dq.front();
            dq.pop_front();

            ans[curr] = counter;
            counter++;

            for (int neighbor : rev_adj[curr]) {
                outdegree[neighbor]--;

                if (outdegree[neighbor] == 0) dq.pb(neighbor);
            }
        }
    }
};

UnweightedGraph g;

void solve() {
    cin >> n;
    vector<pii> inp(n);
    f0r(i, n) {
        int p, c;
        cin >> p >> c;
        p--; // 0-index
        inp[i] = {p, c};
    }

    int root;
    g.init(n, n - 1, false);
    f0r(i, n) {
        if (inp[i].f >= 0) {
            g.parent[inp[i].f].pb(i);
            g.child[i] = inp[i].f;
        } else {
            root = i;
        }
        g.global_c[i] = inp[i].s;
    }

    if (g.handle_possible(root) == false) {
        cout << "NO" << endl;
        return;
    }

    g.get_smaller();
    DEBUG("===adj===");
    f0r(i, n) {
        DEBUG(i, g.adj[i]);
    }
    g.assign_order();

//    f0r(i, n) {
//        if (g.ans[i] == -1) {
//            cout << "NO" << endl;
//            return;
//        }
//    }

    cout << "YES" << endl;
    f0r(i, n) {
        cout << g.ans[i] << " ";
    }
    cout << endl;

    DEBUG(g.parent);
}
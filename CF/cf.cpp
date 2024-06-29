#include <bits/stdc++.h>

using namespace std;
using ll = long long;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = c - 1; a >= b; a--)
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

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
// rng() gives a better random unsigned 32 bit number

ll q, Q, T, k, x, y, z;
int n, m;

void solve();

// Problem URL:
int main() {
    io;
//    usaco("f_cf");
    long long test_cases = 1;
    cin >> test_cases;

    for (int i = 0; i < test_cases; i++) {
        solve();
    }
}

class SegTreeNode {
public:
    ll sum;
    int left; // left range inclusive
    int right; // right range inclusive

    ll lazy_add; // lazy marker on adding
    bool should_lazy_add;
    ll lazy_set; // lazy marker on setting a value

    SegTreeNode* left_node;
    SegTreeNode* right_node;

    SegTreeNode() {
        this->lazy_add = 0;
        this->should_lazy_add = false;
        this->lazy_set = -1;

        this->left_node = nullptr;
        this->right_node = nullptr;
    }

    /**
     * Make the inp vector of size power of 2 by filling in dummy values
     */
    static void __make_inp_power_of_2(vector<ll>& inp, ll dummy) {
        int sz_lg = __lg(inp.size());
        int sz = 1;
        for (int i = 0; i < sz_lg; i++) {
            sz <<= 1;
        }

        if (sz < inp.size()) {
            sz <<= 1;
        }

        int leftover = sz - inp.size(); // amt of 0s to append to the end
        for (int i = 0; i < leftover; i++) {
            inp.push_back(dummy);
        }
    }

    /**
     * Initialize the entire SegTree with this current node as the root (of the subtree) based on inp vector of values
     */
    void init(vector<ll>& inp, int left, int right) {
        this->left = left;
        this->right = right;

        if (left == right) {
            this->sum = inp[left];
            return;
        }

        int mid = (left + right)/2;
        this->left_node = new SegTreeNode();
        this->right_node = new SegTreeNode;
        this->left_node->init(inp, left, mid);
        this->right_node->init(inp, mid + 1, right);
        this->sum = this->left_node->sum + this->right_node->sum;
    }

    /**
     * Evaluate lazy prop for this node
     */
    void eval_lazy() {
        int range = (this->right - this->left + 1);
        if (this->lazy_set > -1) {
            this->sum = this->lazy_set * range;

            if (this->left_node != nullptr) {
                this->left_node->lazy_set = this->lazy_set;
                this->left_node->lazy_add = 0;
            }

            if (this->right_node != nullptr) {
                this->right_node->lazy_set = this->lazy_set;
                this->right_node->lazy_add = 0;
            }

            this->lazy_set = -1;
        }

        if (should_lazy_add) {
            this->sum += this->lazy_add * range;

            if (this->left_node != nullptr) {
                this->left_node->lazy_add += this->lazy_add;
                this->left_node->should_lazy_add = true;
            }

            if (this->right_node != nullptr) {
                this->right_node->lazy_add += this->lazy_add;
                this->right_node->should_lazy_add = true;
            }

            this->lazy_add = 0;
            should_lazy_add = false;
        }
    }

    /**
     * Query the sum of the left and right range
     * TODO: Fancy templating where I pass Case1 Case2 etc. as maybe functions to run
     */
    ll query(int left, int right) {
        eval_lazy();

        if (this->left >= left && this->right <= right) {
            // Case 1 subset
            return this->sum;
        } else if (this->right < left || this->left > right) {
            // Case 2 outside
            return 0;
        }

        // Case 3 partially inside and partially outside
        return this->left_node->query(left, right) + this->right_node->query(left, right);
    }

    void add(int left, int right, int val) {
        eval_lazy();

        if (this->left >= left && this->right <= right) {
            this->lazy_add += val;
            should_lazy_add = true;
            eval_lazy();
            return;
        } else if (this->right < left || this->left > right) {
            return;
        }

        should_lazy_add = true;
        this->left_node->add(left, right, val);
        this->right_node->add(left, right, val);

        this->sum = this->left_node->sum + this->right_node->sum;
    }

    void set(int left, int right, int val) {
        eval_lazy();

        if (this->left >= left && this->right <= right) {
            this->lazy_set = val;
            this->lazy_add = 0;
            eval_lazy();
            return;
        } else if (this->right < left || this->left > right) {
            return;
        }

        this->left_node->set(left, right, val);
        this->right_node->set(left, right, val);

        this->sum = this->left_node->sum + this->right_node->sum;
    }

    void debug_leaves() const {
        if (this->left == this->right) {
            DEBUG(this->left, this->right, this->sum, this->should_lazy_add);
        }

        if (this->left_node != nullptr) {
            this->left_node->debug_leaves();
        }

        if (this->right_node != nullptr) {
            this->right_node->debug_leaves();
        }
    }
};

class Graph {
public:
    int n;
    vector<vector<int>> adj;
    vector<bool> visited;
    vector<int> enter;
    vector<int> rev;
    vector<int> exit;
    vector<int> depth;

    int counter;

    Graph() {}

    void init() {
        adj = vector<vector<int>>(n);
        visited = vector<bool>(n, false);

        counter = 0;
        enter = vector<int>(n, -1);
        rev = vector<int>(n, -1);
        exit = vector<int>(n, -1);
        depth = vector<int>(n, 0);
    }

    void init_adj() {
        init();

        f0r(i, n - 1) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }

    void dfs(int node) {
        enter[node] = counter;
        rev[counter] = node;
        counter++;
        visited[node] = true;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                depth[neighbor] = depth[node] + 1;
                dfs(neighbor);
            }
        }

        exit[node] = counter - 1;
    }
};

void solve() {
    cin >> n >> q;

    vector<int> init(n);
    f0r(i, n) {
        cin >> init[i];
    }

    Graph g;
    g.n = n;
    g.init_adj();
    g.dfs(0);

    vector<ll> seg_init(n, 0);
    SegTreeNode st;
    st.init(seg_init, 0, n - 1);

    set<int> blacks;
    f0r(i, n) {
        if (init[i] == 1) {
            // this node became black
            blacks.insert(g.enter[i]);
            int l = g.enter[i];
            int r = g.exit[i];
            st.add(l, r, 1);
        }
    }

//    f0r(j, n) {
//        st.query(j, j);
//    }
//    st.debug_leaves();
//    DEBUG("==========");

    f0r(i, q) {
        int query;
        cin >> query;
        query--;

        int l = g.enter[query];
        int r = g.exit[query];

        if (blacks.count(g.enter[query])) {
            // black -> white
            st.add(l, r, -1);
            blacks.erase(g.enter[query]);
        } else {
            // white -> black
            st.add(l, r, 1);
            blacks.insert(g.enter[query]);
        }

        if (blacks.empty()) {
            cout << "No" << "\n";
            continue;
        }
        // handle blacks.size() == 1 case?
        if (blacks.size() == 1) {
            cout << "Yes" << "\n";
            continue;
        }

        auto it = blacks.begin();

        int root = *it;
        int endpoint = *blacks.rbegin();
        int other = *(--blacks.upper_bound(g.exit[g.rev[*(++it)]]));

        DEBUG(root, endpoint, other);

//        DEBUG(query);
//        DEBUG(blacks);
//        f0r(j, n) {
//            st.query(j, j);
//        }
//        st.debug_leaves();
//        DEBUG(root, endpoint, other);

        if (other == endpoint || other == root) {
            // we are in case 1, it's just one line and root is one endpoint
            DEBUG("case 1");

            if (st.query(endpoint, endpoint) == blacks.size()) {
                if (g.depth[g.rev[endpoint]] - g.depth[g.rev[root]] == blacks.size() - 1) {
                    cout << "Yes" << "\n";
                } else {
                    cout << "No" << "\n";
                }
            } else {
                cout << "No" << "\n";
            }
        } else {
            // it's an upside down V branch
            DEBUG("case 2");

//            DEBUG(st.query(endpoint, endpoint), st.query(other, other), blacks.size());

            if (st.query(endpoint, endpoint) + st.query(other, other) - 1 == blacks.size()) {
//                DEBUG(g.depth[g.rev[root]], g.depth[g.rev[endpoint]], g.depth[g.rev[other]]);
                if ((g.depth[g.rev[endpoint]] - g.depth[g.rev[root]]) + (g.depth[g.rev[other]] - g.depth[g.rev[root]]) + 1 == blacks.size()) {
                    cout << "Yes" << "\n";
                } else {
                    cout << "No" << "\n";
                }
            } else {
                cout << "No" << "\n";
            }
        }
    }
}

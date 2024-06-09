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

ll q, Q, T, k, l, r, x, y, z;
int n, m;

void solve();

// Problem URL: https://cses.fi/problemset/task/1735
int main() {
    io;
    long long test_cases = 1;
//    cin >> test_cases;

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
    ll lazy_set; // lazy marker on setting a value

    SegTreeNode* left_node;
    SegTreeNode* right_node;

    SegTreeNode() {
        this->lazy_add = 0;
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
            }

            if (this->right_node != nullptr) {
                this->right_node->lazy_set = this->lazy_set;
            }

            this->lazy_set = -1;
        }

        if (this->lazy_add > 0) {
            this->sum += this->lazy_add * range;

            if (this->left_node != nullptr) {
                this->left_node->lazy_add += this->lazy_add;
            }

            if (this->right_node != nullptr) {
                this->right_node->lazy_add += this->lazy_add;
            }

            this->lazy_add = 0;
        }
    }

    /**
     * Query the sum of the left and right range
     * TODO: Fancy templating where I pass Case1 Case2 etc. as maybe functions to run
     */
    ll query(int left, int right) {
        eval_lazy();

        if (this->left >= left && this->right <= right) {
            // Case 1
            return this->sum;
        } else if (this->right < left || this->left > right) {
            // Case 2
            return 0;
        }

        ll ret = 0;
        if (this->left_node != nullptr) {
            // Case 3 Left
            ret += this->left_node->query(left, right);
        }
        if (this->right_node != nullptr) {
            // Case 3 Right
            ret += this->right_node->query(left, right);
        }

        return ret;
    }

    void add(int left, int right, int val) {
        DEBUG(this->sum, this->left, this->right, this->lazy_add);
        eval_lazy();
        DEBUG("eval_lazy1");

        if (this->left >= left && this->right <= right) {
            DEBUG("case 1");
            this->lazy_add += val;
            DEBUG(this->sum, this->left, this->right, this->lazy_add);
            eval_lazy();
            DEBUG("eval_lazy2");
            return;
        } else if (this->right < left || this->left > right) {
            DEBUG("case 2");
            return;
        }
        DEBUG("case 3");

        if (this->left_node != nullptr) {
            this->left_node->add(left, right, val);
        }
        if (this->right_node != nullptr) {
            this->right_node->add(left, right, val);
        }
    }

    void set(int left, int right, int val) {
        eval_lazy();

        if (this->left >= left && this->right <= right) {
            this->lazy_set = val;
            eval_lazy();
            return;
        } else if (this->right < left || this->left > right) {
            return;
        }

        if (this->left_node != nullptr) {
            this->left_node->set(left, right, val);
        }
        if (this->right_node != nullptr) {
            this->right_node->set(left, right, val);
        }
    }

    void debug_leaves() const {
        if (this->left == this->right) {
            DEBUG(this->left, this->right, this->sum);
        }

        if (this->left_node != nullptr) {
            this->left_node->debug_leaves();
        }

        if (this->right_node != nullptr) {
            this->right_node->debug_leaves();
        }
    }
};

void solve() {
    cin >> n >> q;
    vector<ll> inp(n);

    f0r(i, n) {
        cin >> inp[i];
    }

    SegTreeNode root;
    root.init(inp, 0, n - 1);

    f0r(i, q) {
        // process q queries
        int q_case, a, b, x;
        cin >> q_case >> a >> b;
        a--; b--;
        DEBUG(q_case, a, b);

        switch(q_case) {
            case 1:
                cin >> x;
                root.add(a, b, x);
                root.debug_leaves();
                break;
            case 2:
                cin >> x;
                root.set(a, b, x);
                break;
            default:
                // case == 3
                cout << root.query(a, b) << "\n";
        }
    }
}
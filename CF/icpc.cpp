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

vector<int> num_zeros_v; // [0] is before the start
vector<int> zero_index;
map<int, int> closest_lefter_zero;
string s;
vector<int> num_zeros_v_r; // [0] is before the start
vector<int> zero_index_r;
map<int, int> closest_righter_zero;

// both inclusive
ll num_zeros(int left, int right, bool dp_l) {
    DEBUG("num_zeros", left, right);
    if (dp_l) {
        return num_zeros_v[right + 1] - num_zeros_v[left];
    } else {
        return num_zeros_v_r[right + 1] - num_zeros_v_r[left];
    }
}

vector<vector<ll>> dp_left(int x) {
    /* dp left */
    vector<vector<ll>> dp_l(k + 1, vector<ll>(zero_index.size(), INT_MAX));
    // dp_l[0] is useless, if 0 groups achieved so far, clearly cost is 0
    for (int i = 0; i < zero_index.size(); i++) dp_l[0][i] = 0;

    // dp_l[k][i] is the minimum cost to achieve k groups to the left (non-inclusive) of the ith zero index

    // dp_l[1][0]
    if (zero_index[0] >= x) {
        dp_l[1][0] = 0;
    }
//    DEBUG(dp_l[1][0]);

    for (int k_ind = 1; k_ind < k + 1; k_ind++) {
        deque<int> dq;
//        DEBUG(k_ind);

        // if there is a 1 at the start
//        if (s[0] == '1') dq.pb(0);
        dq.pb(0);
        for (int i = 0; i < zero_index.size(); i++) {
//            DEBUG(i, dq);

//            DEBUG(zero_index[i], dq.front(), x);
            // check new transition
            while (!dq.empty() && zero_index[i] - dq.front() >= x) {
                int front = dq.front();
                dq.pop_front();

                if (front == 0 && k_ind > 1) {
                    // cannot have more than one group if we are at the start
                    continue;
                } else if (front == 0 && k_ind == 1) {
                    ll cost = num_zeros(front, zero_index[i] - 1, true);

                    dp_l[k_ind][i] = min(dp_l[k_ind][i], cost);
                    continue;
                }

                ll cost = num_zeros(front, zero_index[i] - 1, true) + dp_l[k_ind - 1][closest_lefter_zero[front]];
                dp_l[k_ind][i] = min(dp_l[k_ind][i], cost);
            }
            dq.pb(zero_index[i] + 1);
            if (i < zero_index.size() - 1) {
                // push DP
                dp_l[k_ind][i + 1] = dp_l[k_ind][i];
            }
        }
    }

    return dp_l;
}

vector<vector<ll>> dp_right(int x) {
    vector<vector<ll>> dp_r(k + 1, vector<ll>(zero_index_r.size(), INT_MAX));
    // dp_l[0] is useless, if 0 groups achieved so far, clearly cost is 0
    for (int i = 0; i < zero_index_r.size(); i++) dp_r[0][i] = 0;

    // dp_r[k][i] is the minimum cost to achieve k groups to the left (non-inclusive) of the ith zero index

    // dp_r[1][0]
    if (zero_index_r[0] >= x) {
        dp_r[1][0] = 0;
    }
    DEBUG(dp_r[1][0]);

    for (int k_ind = 1; k_ind < k + 1; k_ind++) {
        deque<int> dq;
        DEBUG(k_ind);

        // if there is a 1 at the start

        /* END */
//        if (s[n - 1] == '1') {
//            dq.pb(0);
//        } else {
//            dq.pb(-1);
//        }
        dq.pb(0);
        for (int i = 0; i < zero_index_r.size(); i++) {
            DEBUG(i, dq);

            DEBUG(zero_index_r[i], dq.front(), x);
            // check new transition
            while (!dq.empty() && zero_index_r[i] - max(0, dq.front()) >= x) {
                int front = dq.front();
                front = max(0, front);
                dq.pop_front();

                if (front == 0 && k_ind > 1) {
                    // cannot have more than one group if we are at the start
                    continue;
                } else if (front == 0 && k_ind == 1) {
                    ll cost = num_zeros(front, zero_index_r[i] - 1, false);

                    dp_r[k_ind][i] = min(dp_r[k_ind][i], cost);
                    continue;
                }

//                ll cost =
                DEBUG("getting le cost", k_ind - 1, closest_righter_zero[front], zero_index_r[i], i);
                ll broken_zeros = num_zeros(front, zero_index_r[i] - 1, false);
                DEBUG("broken_zeros", broken_zeros);
                DEBUG("dp_r[k_ind - 1][closest_righter_zero[front]]", dp_r[k_ind - 1][closest_righter_zero[front]]);
                ll cost = num_zeros(front, zero_index_r[i] - 1, false) + dp_r[k_ind - 1][closest_righter_zero[front]];
                dp_r[k_ind][i] = min(dp_r[k_ind][i], cost);
            }
            dq.pb(zero_index_r[i] + 1);
            if (i < zero_index_r.size() - 1) {
                // push DP
                dp_r[k_ind][i + 1] = dp_r[k_ind][i];
            }
        }
    }

    return dp_r;
}

bool solve(int x) {
    vector<vector<ll>> dp_l = dp_left(x);
    DEBUG("got dp_l");
    vector<vector<ll>> dp_r = dp_right(x);

    DEBUG("got dp_l and dp_r");

    for (int i = 0; i < dp_l.size(); i++) {
        DEBUG(dp_l[i]);
    }
    for (int i = 0; i < dp_r.size(); i++) {
        DEBUG(dp_r[i]);
    }

    if (k > 1) {
        for (int k_ind = 1; k_ind < k; k_ind++) { // start at 1, end at k instead of k + 1. this is because you have to use at least 1 from left and right, separated by a zero
            // - 1, since I need a 0 separating the left group and the right group since you need multiple groups
            for (int i = 0; i < zero_index.size() - 1; i++) {
                // if left + right <= m, return true

                // left is DP[k_ind][i]
                // right is DP[k - k_ind][zero_index.size() - i - 1]

                ll left_cost = dp_l[k_ind][i];
                ll right_cost = dp_r[k - k_ind][zero_index_r.size() - i - 1];

                if (left_cost + right_cost <= m) {
                    DEBUG(k_ind, k - k_ind);
                    DEBUG(k_ind, i, left_cost, right_cost);
                    return true;
                }
            }
        }
    } else {
        // k == 1
        DEBUG(dp_l[k][zero_index.size() - 1]);
        if (dp_l[k][zero_index.size() - 1] <= m) {
            return true;
        }
    }

    return false;
}

// Problem URL:
int main() {
    io;
    cin >> n >> m >> k;
    num_zeros_v = vector<int>(n + 1);
    num_zeros_v_r = vector<int>(n + 1);

    cin >> s;

    int last_zero = -1;
    for (int i = 0; i < n; i++) {
        num_zeros_v[i + 1] = num_zeros_v[i] + (s[i] == '0');
        if (s[i] == '0') {
            zero_index.pb(i);
            last_zero++; // not the direct ind, but the zero_index ind
        } else {
            closest_lefter_zero[i] = last_zero;
        }
    }

    string s_rev = s;
    reverse(s_rev.begin(), s_rev.end());
    last_zero = -1;
    for (int i = 0; i < n; i++) {
        num_zeros_v_r[i + 1] = num_zeros_v_r[i] + (s_rev[i] == '0');
        if (s_rev[i] == '0') {
            zero_index_r.pb(i);
            last_zero++; // not the direct ind, but the zero_index ind
        } else {
            closest_righter_zero[i] = last_zero;
        }
    }

    DEBUG("finished IO");

    bool ret = solve(1);
    DEBUG(ret);
    int l = 1;
    int r = n;
    int res = -1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (solve(m)) {
            res = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    cout << res << endl;
}
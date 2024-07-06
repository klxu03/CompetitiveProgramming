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
//#define DEBUG(...) 6

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
ll MAXX;

int solve(vector<int>& inp);

int brute_solve(vector<int>& inp) {
    vector<int> num_cakes;
    set<int> uniq;
    f0r(i, n) {
        if (uniq.count(inp[i]) == 0) {
            uniq.insert(inp[i]);
            num_cakes.pb(0);
        }

        num_cakes.back()++;
    }

    const int sz = num_cakes.size();
    int ret = INT_MAX;
    vector<int> optimal;
    for (ll tc = 0; tc < (1 << sz); tc++) {
        vector<int> use(sz, 0); // 1 means Bob eats this cake
        int ind = 0;
        for (int i = (1 << (sz - 1)); i > 0; i >>= 1) {
            if ((tc & i) != 0) {
                use[ind] = 1;
            }

            ind++;
        }

        // check if this is allowed
        int alice_ate = 0;
        int bob_ate = 0;
        bool valid = true;

        for (int i = 0; i < sz; i++) {
            if (use[i]) {
                bob_ate += num_cakes[i];
            } else {
                alice_ate++;
            }

            if (bob_ate > alice_ate) {
                valid = false;
            }
        }

        if (!valid) continue;

        if (alice_ate < ret) {
            ret = alice_ate;
            optimal = use;
        }
    }

    DEBUG(num_cakes);
    DEBUG(optimal);

    return ret;
}

/*
// Problem URL:
int main() {
    io;
//    usaco("f_cf");
    long long test_cases = 1;
    cin >> test_cases;

    for (int i = 0; i < test_cases; i++) {
        cin >> n;
        vector<int> inp(n);

        f0r(i, n) {
            cin >> inp[i];
        }
        sort(inp.begin(), inp.end());

        brute_solve(inp);
        solve(inp);
    }
}
*/

int main() {
    n = 23;
    MAXX = 99;
    for (int i = 0; i < 1; i++) {
        vector<int> inp(n);

        for (int j = 0; j < n; j++) {
            inp[j] = rng() % 7;
        }
        sort(inp.begin(), inp.end());

        inp = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 4, 4, 5, 5, 5, 5, 5, 6};

        int brute_solve_ret = brute_solve(inp);
        int solve_ret = solve(inp);
        if (brute_solve_ret != solve_ret) {
            cout << "FAILED: " << endl;
            for (int j = 0; j < n; j++) {
                cout << inp[j] << ", ";
            }
            cout << endl;
            cout << "Got: " << solve_ret << " | Expected: " << brute_solve_ret << endl;
            return -1;
        }
    }
}

int solve(vector<int>& inp) {
    vector<int> num_cakes;
    set<int> uniq;
    f0r(i, n) {
        if (uniq.count(inp[i]) == 0) {
            uniq.insert(inp[i]);
            num_cakes.pb(0);
        }

        num_cakes.back()++;
    }

    const int sz = num_cakes.size();
    vector<vector<ll>> dp(sz + 1, vector<ll>(sz + 1, MAXX));
    // dp[i][j] is the min number of turns for Bob to completely eaten j cakes before the i-th turn
    // Alice is trying to eat the (i + j)th cake right now, so Bob now has the opportunity to have eaten all of the (i + j)th cake before the i-th turn
    // need dp[i - 1][j - 1] + num_cakes[i + j] < dp[i - 1][j] to replace

    for (int i = 0; i < sz + 1; i++) {
        dp[i][0] = 0;
    }

    for (int i = 1; i < sz + 1; i++) {
        // we are currently on time i
        for (int j = 1; j < sz + 1; j++) {
            // Bob is going to have eaten j cakes now

            if (dp[i - 1][j - 1] == MAXX) break;
            if (j > i) break;
            if (i + j > sz) break;

            dp[i][j] = dp[i - 1][j];

//            if (j == i) break;
            if (dp[i - 1][j - 1] + num_cakes[i + j - 1] > i) break;
            DEBUG(num_cakes[i + j - 1]);
            DEBUG(i, j);

            // Alice is going to have eaten the (i + j)th cake now, new opp at (i + j - 1) to eat before
            dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + num_cakes[i + j - 1]);
        }
    }

    // now u gotta do the right-half to add
    vector<vector<int>> cost(sz + 1, vector<int>(sz + 1, 0)); // cost[i][j] means that Alice is eating ith cake, j is max num cakes Bob can have

    multiset<int> ms; // multiset of cake sizes
    // Alice eating the sz-th cake, Bob can't eat any
    for (int i = sz - 1; i >= 0; i--) {
        ms.insert(num_cakes[i]); // Bob newly has the option to eat this cake

        auto it = ms.begin();
        int counter = 0;
        int sum = 0;
        // Bob can eat up to j total cakes
        DEBUG(i, ms);
        for (int j = 1; j < sz + 1; j++) {
            if (it != ms.end() && sum + *it <= j) {
                sum += *it;
                it++;
                counter++;

                DEBUG(sum, j, counter);
            }

            cost[i][j] = counter;
        }
    }

    DEBUG(num_cakes);
    f0r(i, sz + 1) {
        DEBUG(i, dp[i]);
    }
    DEBUG(num_cakes);
    f0r(i, sz + 1) {
        DEBUG(i, cost[i]);
    }

    DEBUG(num_cakes);
    int max_j = -1; // j that can be eaten + cost[i][j]
    for (int i = 0; i < sz + 1; i++) {
        for (int j = 0; j < sz + 1; j++) {
            if (dp[i][j] < MAXX) {
                int leftover_j = i - dp[i][j];

                max_j = max(max_j, j);
                if (max_j < j) {
                    DEBUG("update", max_j, j);
                }

                int alice_eat = i + j;
                if (alice_eat > sz) continue;
                if (max_j < j + cost[alice_eat][leftover_j]) {
                    DEBUG("update", max_j, j + cost[alice_eat][leftover_j], i, j, alice_eat, leftover_j);
                }
                max_j = max(max_j, j + cost[alice_eat][leftover_j]);
            }
        }
    }

    DEBUG(sz, max_j);

//    cout << sz - max_j << endl;
    return sz - max_j;
}

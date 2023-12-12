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

// Problem URL:
int main() {
    io;
    long long test_cases = 1;
     cin >> test_cases;

    for (int i = 0; i < test_cases; i++) {
        solve();
    }
}

void solve() {
    cin >> n;
    vector<ll> inp(n);
    vector<ll> next_real_num(n, -1); // index of the next real num

    int prev_real_num = 0;
    ll tot_sum = 0;
    f0r(i, n) {
        cin >> inp[i];

        tot_sum += inp[i];
        if (inp[i] > 1) {
            next_real_num[prev_real_num] = i;
            prev_real_num = i;
        }
    }

    vector<ll> pref(n);
    pref[0] = inp[0];
    for (int i = 1; i < n; i++) {
        pref[i] = pref[i - 1] + inp[i];
    }

    ll best = 1;
    int begin_1s = 0;
    int end_1s = 0;
    for (int i = 0; i < n; i++) {
        if (begin_1s == i && inp[i] == 1) {
            begin_1s++;
        }

        best *= inp[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        if (inp[i] != 1) {
            break;
        }

        end_1s++;
    }

    best += begin_1s + end_1s;

    if (begin_1s == n) {
        cout << 1 << " " << 1 << endl;
        return;
    }

    pii best_pair = {begin_1s + 1, n - end_1s};
    DEBUG(best, best_pair);

    for (int i = 0; i < n; i++) {
        // i marks the starting index, never start at a 1
        if (inp[i] == 1) continue;
        for (int size = 0; size <= 30; size++) {
            // jump up to size forward real nums, with next_real_num jumping
            // size = 1 means we are combining with 1 number, so 2 total

            // calculate how many we've jumped, subtract the prefix sum in that area from tot_sum and add the product from jumping this much
            int curr = i;
            ll prod = inp[i];
            for (int jump = 0; jump < size; jump++) {
                int next = next_real_num[curr];
                if (next == -1) {
                    break;
                }

                prod *= inp[next];
                curr = next; 
            }

            ll new_sum = prod + tot_sum - pref[curr];
            // lower half of prefix sum
            if (i > 0) {
                new_sum -= pref[i - 1];
            }

            if (new_sum > best) {
                best = new_sum;
                best_pair = {i + 1, curr + 1};
            }
        }
    }

    cout << best_pair.f << " " << best_pair.s << endl;
}
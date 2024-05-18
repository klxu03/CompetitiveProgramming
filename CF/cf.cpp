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

/*
 * Fox loves permutations! She came up with the following problem and asked Cat to solve it:

You are given an even positive integer 𝑛
 and a permutation†
 𝑝
 of length 𝑛
.

The score of another permutation 𝑞
 of length 𝑛
 is the number of local maximums in the array 𝑎
 of length 𝑛
, where 𝑎𝑖=𝑝𝑖+𝑞𝑖
 for all 𝑖
 (1≤𝑖≤𝑛
). In other words, the score of 𝑞
 is the number of 𝑖
 such that 1<𝑖<𝑛
 (note the strict inequalities), 𝑎𝑖−1<𝑎𝑖
, and 𝑎𝑖>𝑎𝑖+1
 (once again, note the strict inequalities).

Find the permutation 𝑞
 that achieves the maximum score for given 𝑛
 and 𝑝
. If there exist multiple such permutations, you can pick any of them.

†
 A permutation of length 𝑛
 is an array consisting of 𝑛
 distinct integers from 1
 to 𝑛
 in arbitrary order. For example, [2,3,1,5,4]
 is a permutation, but [1,2,2]
 is not a permutation (2
 appears twice in the array), and [1,3,4]
 is also not a permutation (𝑛=3
 but there is 4
 in the array).

Input
The first line of input contains an integer 𝑡
 (1≤𝑡≤104
) — the number of test cases in the input you will have to solve.

The first line of each test case contains one even integer 𝑛
 (4≤𝑛≤105
, 𝑛
 is even) — the length of the permutation 𝑝
.

The second line of each test case contains the 𝑛
 integers 𝑝1,𝑝2,…,𝑝𝑛
 (1≤𝑝𝑖≤𝑛
). It is guaranteed that 𝑝
 is a permutation of length 𝑛
.

It is guaranteed that the sum of 𝑛
 across all test cases doesn't exceed 105
.

Output
For each test case, output one line containing any permutation of length 𝑛
 (the array 𝑞
), such that 𝑞
 maximizes the score under the given constraints.


 Example Input
 4
4
1 2 3 4
4
4 3 1 2
6
6 5 1 4 2 3
8
1 2 4 5 7 6 8 3

 Example output
 2 4 1 3
3 1 4 2
2 5 1 4 3 6
5 4 8 2 7 1 6 3
 */

bool possible(int k, vector<ll>& inp, map<int, int>& pos) {
    ll want = (n - k + 1) * 2;
}

void solve() {
    cin >> n;
    vector<ll> inp(n);
    // pos map from int to int such that pos[5] = 3 means 5 is at index 3
    // keys are sorted from biggest first to smallest last
    map<int, int, greater<int>> pos;

    f0r(i, n) {
        cin >> inp[i];
        pos[inp[i]] = i;
    }


}

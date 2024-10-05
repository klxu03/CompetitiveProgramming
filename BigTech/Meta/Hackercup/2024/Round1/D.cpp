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
/**
Notice that when we are trying to maximize the number of decodings, we want to replace ? with the smallest possible digit. This is because the smallest digit is 1. It can pair with the previous digit if it is <= 2 to form letters, and it can be used to form a letter with the next number paired together.
However, we need the K-th largest uncorrupted strings, so we need to sort the uncorrupted strings in lexicographical order and find the K-th largest.

There are actually two different problems we need to solve:
1. Find the K-th largest uncorrupted string.
2. Calculate the number of decodings possible for a given uncorrupted string.

We will start by trying to solve the first problem.

We define a group of ? as consecutive question marks in the encoded string. For example, in the encoded string ??2??01, there are two groups of ?: ??2 and 2??0. We only care about what is immediately in front and after the group.
Within each group of ?, we can calculate the number of valid possible decodings that maintain the maximum number of decodings. Then following multiple groups, we multiply the number of decodings together to get the total number of decodings for the uncorrupted string.

We will use this idea to iterate through the encoded string and calculate the maximum current lexographically largest uncorupted string we can produce and which K-th largest we are if we replace all future ? with 1. 
Then at some point we can narrow it down to a range where we have to pick the next ? to be a specific number to make it the K-th largest.

We notice that any intermediary ? has to be either a 1 or a 2 to maintain the maximum number of decodings. This is because if we pick a number greater than 2, we will not be able to pair it with the next digit to form a letter. 
If it is an ending ?, then we need to check the number directly after the group of ? to see if it is >= 6. 
If it is, then we can only pick 1 to maintain the maximum number of decodings. Otherwise, we can pick 1 or 2.

If we are looking at a singleton ?, then we also need to consider the number directly before the group of ? to see if it is = 2.
If it is 1, we are free to do whatever. If it is 2, then the following number has to be <= 6 to maintain the maximum number of decodings.

We should use dynamic programming to calculate the number of decodings for a group of ?. 
Treating each group in isolation, we need to calculate the number of decodings possible for a group of ? of size i + 1, but we do not care about the last ? since that value is dependent on the number directly after the group of ?.

We define dp[i] as the number of decodings possible for a group of ? of size i + 1, but we will need to additionally multiply it by 2 if the number directly after the group of ? is <= 6 since then this should be either a 1 or a 2 so it can pair with the digit following the group of ? to form a letter. However, if it is >6, then we should multiply this amount by 10 since we can pick any number from 0 to 9 to pair with the previous 1 or 2 to form a letter. We do not need to care about the number directly after. 
We don't care about the number directly before since this letter needs to be 1 or 2 regardless to pair with the 2nd ?.

We should handle the singleton ? seperately.

Now we have an idea of the number of K-th largest uncorrupted strings we can produce for a group of ?. We need to multiply this by the number of decodings possible for the previous group of ? and the following group of ? to get the total number of decodings possible for the uncorrupted string.

We can use the greedy approach to find the K-th largest uncorrupted string. We iterate through the encoded string and try to pick the largest possible digit for each ? group. Then when we try to multiply the next group and it exceeds K, then we need to start iterating through each ? in the group. Multiplying the number of decodings possible by 2 every time we go through a ? in the group. At some point we will no longer be able to multiply by 2 and will have to pick a specific number for the ?. We need to be careful to pick the largest possible number for the ? without exceeding K. 
Following this approach, we will be able to find the K-th largest uncorrupted string.

Now we need to solve the second problem, calculating the number of decodings possible for a given uncorrupted string.
This is quite the counting problem, having to leverage skills from combinatorics and discrete math. 
Here we are assuming that each ? is replaced with 1 when calculating the number of pairings. That way, we can just look at a single possible encoding of numbers with the ? all being replaced with 1 when trying to count the total number of possible decoding of different strings when the ? are replaced with 1.

The number of decodings isn't quite N choose 2, but it is similar. It is not N choose 2 because some pairings do not work, for example if the first number is bigger than 2, there is no pairing. And if the first number in the pair is a 2, then the second number has to be <= 6. 

I don't know how to count the number of decodings possible, I can't do counting. 
 */
int main() {
    io;
    // usaco("f_cf");
    long long test_cases = 1;
    cin >> test_cases;

    for (int i = 0; i < test_cases; i++) {
        solve();
    }
}

void solve() {
    cin >> n;
}

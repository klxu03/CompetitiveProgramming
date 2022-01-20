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
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

ll n, q, Q, T, k, l, r, x, y, z, g;

bool cmp(const array<ll, 3>& x, const array<ll, 3>& y) {
    if (x[1] != y[1]) {
        return x[1] < y[1];
    } else {
        return x[0] < y[0];
    }
}

/* 
can also use sets instead of priority queues
pq.pop() = set.erase(set.begin());
pq.top() = *(set.begin())
pq.push(el) = set.insert(el);
*/

// Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=859
int main() {
    usaco("convention2");
    // io;

    cin >> n;
    vector<array<ll, 3> > cows(n); // cows[0] is the seniority, cows[1] is time appears, cows[2] is time will spend eating
    f0r(i, n) {
        ll first, second;
        cin >> first >> second;
        cows[i] = {i, first, second};
    }

    sort(cows.begin(), cows.end(), cmp);
    DEBUG(cows);

    ll time = 0;
    ll longest = 0;
    ll seen_counter = 0; // number of cows added to priority queue
    ll eaten_counter = 0; // counter for cows finished eating

    priority_queue<array<ll, 3>, vector<array<ll, 3> >, greater<array<ll, 3> > > pq;

    while(eaten_counter < n) {
        // With current time, add cows that should be in line
        while(seen_counter < n && time > cows[seen_counter][1]) {
            pq.push(cows[seen_counter]);
            seen_counter++;
        }

        // If the pq is currently empty, need to skip ahead in time to next cow
        if(seen_counter < n && pq.empty()) {
            pq.push(cows[seen_counter]);
            time = cows[seen_counter][1];
            seen_counter++;
        }

        // Have the next cow eat
        array<ll, 3> top = pq.top();
        pq.pop();

        ll diff = time - top[1];
        if(diff > longest) longest = diff;

        DEBUG(time, top[1], diff, seen_counter, eaten_counter);
        time += top[2];
        
        eaten_counter++;
        DEBUG(top);
    }
    DEBUG(time, seen_counter, eaten_counter);
    cout << longest << endl;

}   
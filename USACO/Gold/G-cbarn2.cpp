#include <bits/stdc++.h>

using namespace std;

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define max3(a, b, c) max(a, max(b, c))
#define pb push_back
#define f first
#define s second
#define mp(a, b) make_pair(a, b)

using ll = long long;

/* Print a vector */
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {cout << "[";for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];}return cout << "]";}

/* For Debugging Purposes */
#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#else
#define DEBUG(...) 6
#endif

template<typename T, typename S> ostream& operator << (ostream &os, const pair<T, S> &p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename C, typename T = decay<decltype(*begin(declval<C>()))>, typename enable_if<!is_same<C, string>::value>::type* = nullptr>
ostream& operator << (ostream &os, const C &c) {bool f = true; os << "["; for (const auto &x : c) {if (!f) os << ", "; f = false; os << x;} return os << "]";}
template<typename T> void debug(string s, T x) {cerr << s << " = " << x << "\n";}
template <typename T, typename... Args> void debug(string s, T x, Args... args) {for (int i=0, b=0; i<(int)s.size(); i++) if (s[i] == '(' || s[i] == '{') b++;
else if (s[i] == ')' || s[i] == '}') b--; else if (s[i] == ',' && b == 0) {cerr << s.substr(0, i) << " = " << x << " | "; debug(s.substr(s.find_first_not_of(' ', i + 1)), args...); break;}}

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

ll n, k;
vector<vector<ll>> cost;

ll saved(int leftmost, int old_rightmost, int new_rightmost) {
    ll old_cost = cost[old_rightmost][leftmost];
    
    // just old_cost - new_cost overcounts an amount "saved" of old right to new right
    // as new_cost doesn't need to calculate this intermediary cost from old to new right
    if (new_rightmost == 0) {
        old_cost -= cost[old_rightmost][n - 1];
    } else {
        old_cost -= cost[old_rightmost][new_rightmost - 1];
    }

    ll new_cost = cost[new_rightmost][leftmost];

    return old_cost - new_cost;    
}

int main() {
    io;
    cin >> n >> k;
    vector<ll> inp(n);
    f0r(i, n) {
        cin >> inp[i];
    }

    cost = vector<vector<ll>>(n, vector<ll>(n, 0)); // cost[i][j] is right entrance at i, wrap to left entrace of j, the cost or total distance it takes
    // Populate cost
    f0r(i, n) {
        int sum = 0;
        f0r(j, n) {
            int new_index = (j + i) % n; // wrapped index
            sum += inp[new_index] * j;
            cost[i][new_index] = sum;
        }
    }

    ll ret = LLONG_MAX;
    for (int leftmost = 0; leftmost < n; leftmost++) {
        DEBUG(leftmost);
        ll initial = cost[leftmost][n - 1];
        if (leftmost != 0) initial = cost[leftmost][leftmost - 1];
        // dp[2][8] stores place the 4th entrance at rightmost position 8, cheapest cost
        vector<vector<ll>> dp(k - 1, vector<ll>(n, LLONG_MAX));

        // i == 0 case
        for (int rightmost = 0; rightmost < n; rightmost++) {
            if (leftmost == rightmost) continue;

            dp[0][rightmost] = cost[leftmost][rightmost - 1] + cost[rightmost][leftmost - 1];
        }

        f1r(i, 1, k - 1) {
            for (int rightmost = 0; rightmost < n; rightmost++) {
                if (leftmost == rightmost) continue;

                // find optimal dp[i][rightmost]
                int left_counter = leftmost + 1;
                while (left_counter != rightmost) {
                    // old cost of left_counter that keeps going right - amt saved with new entrance at rightmost
                    dp[i][rightmost] = min(dp[i][rightmost], dp[i - 1][left_counter] - saved(leftmost, left_counter, rightmost));

                    left_counter++;
                    left_counter %= n; // in case left is to "right" of right
                }
            }
        }

        f0r(i, n) {
            ret = min(ret, dp[k - 1][i]);
        }
    }

    cout << ret << endl;
}
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
template<typename T> void debug(string s, T x) {cerr << "\033[1;35m" << s << "\033[0;32m = \033[33m" << x << "\033[0m\n";}
template<typename T, typename... Args> void debug(string s, T x, Args... args) {for (int i=0, b=0; i<(int)s.size(); i++) if (s[i] == '(' || s[i] == '{') b++; else
if (s[i] == ')' || s[i] == '}') b--; else if (s[i] == ',' && b == 0) {cerr << "\033[1;35m" << s.substr(0, i) << "\033[0;32m = \033[33m" << x << "\033[31m | "; debug(s.substr(s.find_first_not_of(' ', i + 1)), args...); break;}}

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

ll n, k;
vector<int> inp;
vector<vector<ll>> prefix;

vector<vector<ll>> dp;

ll saved(int leftmost, int old_right, int new_right) {
    ll old_cost = prefix[old_right][(leftmost - 1 + n) % n];
    ll new_cost = prefix[old_right][(new_right - 1 + n) % n] + prefix[new_right][(leftmost - 1 + n) % n];

    return old_cost - new_cost;
}

int main() {
    // io;
    usaco("cbarn2");
    cin >> n >> k;
    k = min(k, n); // no 4 cows 6 gates situation
    inp = vector<int>(n);
    prefix = vector<vector<ll>>(n, vector<ll>(n));
    dp = vector<vector<ll>>(k, vector<ll>(n)); 

    f0r(i, n) {
        cin >> inp[i];
    }

    // build the prefix 2D array
    f0r(i, n) {
        ll counter = 0;
        ll sum = 0;

        f0r(j, n) {
            sum += counter * inp[(j + i) % n];
            prefix[i][(j + i) % n] = sum;
            counter++;
        }

        // note that the 0th row, dp[0][x] is going to be completely empty since 0th extra gate is N/A
        // ^ this note changed cuz last line in case k = 1, just make it sums
        dp[0][i] = sum;
    }

    ll ret = LLONG_MAX;
    f0r (i, n) {
        ret = min(ret, dp[0][i]);
    }

    f0r(left, n) {
        // could maybe fill the 2D dp matrix with MAX if wanted

        // dp[x][left] is just bruh new gate as same as left
        f0r(i, k) {
            f0r(j, n) {
                dp[i][j] = LLONG_MAX - 1e12;
            }
        }

        // handle the k == 1 special case
        // no particular reason this is the special case, as I'm pretty sure you can generalize this for k == 2 but this is the only one I can hand code to be something else and just make it cleaner why not (just in case)
        if (k >= 2) {
            f1r(j, 1, n) { // dp[1][left] is just bruh new gate as same as left
                dp[1][(left + j) % n] = prefix[left][(left + j - 1) % n] + prefix[(left + j) % n][(left - 1 + n) % n];
            }
        }

        f1r(i, 2, k) {
            f1r(right_counter, i, n) {
                int new_right = (left + right_counter) % n; // can put a gate on new_right

                ll min_val = LLONG_MAX; // trying to find dp[i][new_right]

                int curr_j = (left + i) % n; // the min newest kth gate
                // 3 
                while (curr_j != (new_right + 1) % n) { // keep going until equals new_right
                    min_val = min(min_val, dp[i - 1][curr_j] - saved(left, curr_j, new_right)); 
                    DEBUG(curr_j);
                    DEBUG(dp[i - 1][curr_j], saved(left, curr_j, new_right));
                    
                    curr_j++;
                    curr_j %= n;
                }

                dp[i][new_right] = min_val;
            }
        }

        f0r(j, n) {
            ret = min(ret, dp[k - 1][j]);
        }

        DEBUG(left);
        f0r(i, k) {
            DEBUG(dp[i]);
        }
    }


    cout << ret << endl;
}
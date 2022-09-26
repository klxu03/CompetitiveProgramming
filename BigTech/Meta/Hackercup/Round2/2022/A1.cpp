#include <bits/stdc++.h>

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
#define t third
#define pll pair<ll, ll>

/* For Debugging Purposes */
#ifdef LOCALL
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
    freopen((filename + ".txt").c_str(), "r", stdin);
    freopen((filename + "_output.txt").c_str(), "w", stdout);
}

ll q, Q, T, k, l, r, x, y, z, g;
ll n, m;

void solve(); 

int main() {
	// io
    usaco("perfectly_balanced_chapter_1_input");
	ll test_cases = 1;
    cin >> test_cases;
	
	f0r(test_case, test_cases) {
        cout << "Case #" << test_case + 1 << ": ";
		solve();
	}
}

void solve() {
    string str;
    cin >> str;
    n = str.size();

    vector<vector<int>> dp(n + 1, vector<int>(26, 0));

    dp[1][str[0] - 'a']++; // 1-index
    f1r(i, 2, n + 1) {
        f0r(j, 26) {
            dp[i][j] = dp[i - 1][j];
        }
        dp[i][str[i - 1] - 'a']++;
    }

    cin >> q;
    ll ret = 0;
    f0r(i, q) {
        DEBUG(i);
        int l, r;
        cin >> l >> r;
        l--;
        DEBUG(dp[r]);
        DEBUG(dp[l]);
        if ((r - l) % 2 == 0) { // even # of letters
            DEBUG("even number of letters");
            continue;
        }

        vector<int> right_left(26, 0); // right - left
        f0r(j, 26) {
            right_left[j] = dp[r][j] - dp[l][j];
        }
        DEBUG(right_left);

        vector<int> mid_left(26, 0); // mid - left
        ll mid = (l + r + 1)/2;
        f0r(j, 26) {
            mid_left[j] = dp[mid][j] - dp[l][j];
        }  
        DEBUG(mid_left);

        // Odd letter on left side
        DEBUG("odd_left case");
        bool odd_found = false;
        bool valid = true;
        f0r(j, 26) {
            if (mid_left[j] * 2 != right_left[j]) {
                if (odd_found) {
                    DEBUG("left valid", j);
                    valid = false;
                    break;
                } else {
                    odd_found = true;
                    DEBUG("left odd_found", j);
                }
            }
        }

        DEBUG("left", valid);
        if (valid) {
            ret++;
            continue;
        }

        // Odd letter on right side
        DEBUG("odd_right case");
        mid = (l + r - 1)/2;
        f0r(j, 26) {
            mid_left[j] = dp[mid][j] - dp[l][j];
        }  
        DEBUG(mid_left);

        odd_found = false;
        valid = true;
        f0r(j, 26) {
            if (mid_left[j] * 2 != right_left[j]) {
                if (odd_found) {
                    valid = false;
                    DEBUG("right valid: ", j);
                    break;
                } else {
                    odd_found = true;
                    DEBUG("right odd_found", j);
                }
            }
        }

        if (valid) {
            ret++;
        }
        DEBUG("right", valid);
    }

    cout << ret << endl;
}
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
	// io;
    usaco("perfectly_balanced_chapter_1_input");
    // usaco("copy");
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

    DEBUG("starting new test case", str.size());
    // cin >> q;
    // f0r(i, q) {
    //     ll x;
    //     cin >> x >> x;
    // }

    vector<vector<ll>> dp(26, vector<ll>(str.size() + 1, 0));
    dp[str[0] - 'a'][1] = 1; // Increment first character
    f1r(i, 2, str.size() + 1) {
        f0r(j, 26) {
            dp[j][i] = dp[j][i - 1];
        }
        dp[str[i - 1] - 'a'][i]++;
    }

    // cout << endl;
    // f0r(i, 26) {
    //     char c = 'a' + i;
    //     DEBUG(c, dp[i]);
    // }
    DEBUG("dped the input");

    cin >> q; // q queries
    ll ret = 0;
    f0r(i, q) {
        DEBUG(i);
        ll l, r;
        cin >> l >> r;
        l--; // already 1 indexed
        DEBUG(l, r);

        vector<ll> left_right(26, 0);
        f0r(j, 26) {
            left_right[j] = dp[j][r] - dp[j][l];
        }
        DEBUG(left_right);
        
        int num_odd = 0;
        int odd = -1;
        f0r(j, 26) {
            if (left_right[j] % 2 == 1) {
                num_odd++;
                odd = j;
            }
        }
        // char codd = odd + 'a';
        // DEBUG(num_odd, codd);

        // The error below caused my submission to fail. Needed:
        // if (num_odd >= 2 || num_odd == 0) since case of even length query
        if (num_odd >= 2) {
            continue;
        }

        vector<ll> left_mid(26, 0);
        int mid = (r + l + 1)/2;
        DEBUG(mid);
        f0r(j, 26) {
            left_mid[j] = dp[j][mid] - dp[j][l];
        }

        if (num_odd == 1) {
            // Fix odd query
            if (left_mid[odd] * 2 > left_right[odd]) {
                // the odd one is on the left
                left_mid[odd]--;
            } else {
                // the odd one is on the right, so take out middle one
                int mid_char = str[mid - 1] - 'a';
                // char mid_cchar = mid_char + 'a';
                // DEBUG(mid_char, mid_cchar, left_mid[mid_char]);
                left_mid[mid_char]--;
                // DEBUG(left_mid[mid_char]);
                // DEBUG(str[mid + l - 1]);
            }

            left_right[odd]--; // Subtract the odd on the right
        }

        DEBUG(left_mid);

        bool add = true;
        // Working with an even length now after turning odd into even
        f0r(j, 26) {
            if (left_mid[j] * 2 != left_right[j]) {
                DEBUG(j, left_mid[j], left_right[j]);
                add = false;
                break;
            }
        }
        DEBUG("done checking", add);

        if (add) {
            ret++;
        }
        DEBUG(ret);
    }

    DEBUG("cout ret", ret);
    cout << ret << endl;
}
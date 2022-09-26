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

ll n, m, q, Q, T, k, l, r, x, y, z, g;

void solve(); 

// Problem: https://www.geeksforgeeks.org/check-if-a-word-exists-in-a-grid-or-not/
// ^ but adapted for IP HW3 for 2022 fall 
int main() {
	io;
	ll test_cases = 1;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

vector<string> grid;
string word;

bool in_bounds(ll y, ll x) {
    return y >= 0 && y < n && x >= 0 && x < n;
}

bool check_up(ll y, ll x) {
    f0r(i, word.size()) {
        if (in_bounds(y - i, x) && grid[y - i][x] == word[i]) {
            continue;
        } else {
            return false;
        }
    }

    return true;
}

bool check_down(ll y, ll x) {
    f0r(i, word.size()) {
        if (in_bounds(y + i, x) && grid[y + i][x] == word[i]) {
            continue;
        } else {
            return false;
        }
    }

    return true;
}

bool check_left(ll y, ll x) {
    f0r(i, word.size()) {
        if (in_bounds(y, x - i) && grid[y][x - i] == word[i]) {
            continue;
        } else {
            return false;
        }
    }

    return true;
}

bool check_right(ll y, ll x) {
    f0r(i, word.size()) {
        if (in_bounds(y, x + i) && grid[y][x + i] == word[i]) {
            continue;
        } else {
            return false;
        }
    }

    return true;
}

void solve() {
	cin >> n >> k;
    grid = vector<string>(n);
    vector<string> words(k);
    f0r(i, n) {
        cin >> grid[i];
    }

    f0r(i, k) {
        cin >> words[i];
    }

    f0r(word_counter, k) {
        word = words[word_counter];
        f0r(direction, 4) {
            f0r(i, n) {
                f0r(j, n) {
                    if (direction == 0 && check_right(i, j)) {
                        cout << word << " " << i << " " << j << " R" << endl;
                    }

                    if (direction == 1 && check_left(i, j)) {
                        cout << word << " " << i << " " << j << " L" << endl;
                    }

                    if (direction == 2 && check_down(i, j)) {
                        cout << word << " " << i << " " << j << " D" << endl;
                    }

                    if (direction == 3 && check_up(i, j)) {
                        cout << word << " " << i << " " << j << " U" << endl;
                    }
                }
            }
        }
    }

}
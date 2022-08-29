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

ll r, c;

vector<string> inp;
vector<string> cpy; // cpy of inp that I'm screwing around

void solve(); 

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

// Problem: 
int main() {
    usaco("B2");
	ll test_cases = 1;
    cin >> test_cases;
	
	f0r(test_case, test_cases) {
        cout << "Case #" << test_case + 1 << ": ";
		solve();
	}
}

bool isValid(int i, int j) {
    return i >= 0 && i < r && j >= 0 && j < c; 
}

// Checks if it is possible for this [i][j] cell to have two neighbors right now
bool isPossible(int i, int j) {
    int num_possible_neighbors = 0;
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};

    f0r(k, 4) {
        int newR = i + dr[k];
        int newC = j + dc[k];

        if (isValid(newR, newC) && cpy[newR][newC] != '#') {
            num_possible_neighbors++;
        }
    }

    return num_possible_neighbors >= 2;
}

void solve() {
    cin >> r >> c;
    inp = vector<string>(r);
    cpy = vector<string>(r);

    bool allEmpty = true;
    f0r(i, r) {
        cin >> inp[i];
        cpy[i] = inp[i];
        f0r(j, c) {
            if (inp[i][j] == '^') {
                allEmpty = false;
                break;
            }
        }
    }

    if (allEmpty) {
        cout << "Possible" << endl;
        f0r(i, r) {
            cout << inp[i] << endl;
        }

        return;
    }

    deque<pll> dq;
    vector<int> dr = {-1, 1, 0, 0};
    vector<int> dc = {0, 0, -1, 1};
    f0r(i, r) {
        f0r(j, c) {
            while(!dq.empty()) {
                pll curr = dq.front();
                dq.pop_front();
                // DEBUG(i, j, curr);

                f0r(i, 4) {
                    int newR = curr.f + dr[i];
                    int newC = curr.s + dc[i];

                    if (isValid(newR, newC) && cpy[newR][newC] != '#' && !isPossible(newR, newC)) {
                        if (inp[newR][newC] == '^') {
                            cout << "Impossible" << endl;
                            return;
                        }
                        cpy[newR][newC] = '#';
                        dq.pb(mp(newR, newC));
                    }
                }
            }

            if (!isPossible(i, j)) {
                if (inp[i][j] == '^') {
                    cout << "Impossible" << endl;
                    return;
                }
                cpy[i][j] = '#';
                dq.pb(mp(i, j));
            }
        }
    }

    cout << "Possible" << endl;
    f0r(i, r) {
        string ret = "";
        f0r(j, c) {
            if (cpy[i][j] != '#') {
                ret += '^';
            } else {
                ret += inp[i][j];
            }
        }
        cout << ret << endl;
    }
}
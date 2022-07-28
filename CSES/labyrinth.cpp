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

bool valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

//Problem URL: https://cses.fi/problemset/task/1193 
int main() {
    io;
    cin >> n >> m;

    vector<string> maze(n);
    vector<vector<char>> step(n, vector<char>(m, '*'));
    // step[4][2] is the direct step to reaching position 4, 2
    // so if it is L, that means you were originally at 5, 2 then going L
    pll A, B;
    f0r(i, n) {
        cin >> maze[i];
        f0r(j, m) {
            if (maze[i][j] == 'A') {
                A = mp(i, j);
            } else if (maze[i][j] == 'B') {
                B = mp(i, j);
            }
        }
    }

    f0r(i, n) {
        DEBUG(maze[i]);
    }
    DEBUG(A, B);

    deque<pll> dq;
    dq.pb(A);
    step[A.f][A.s] = '-';
    bool foundB = false;
    while (!dq.empty()) {
        pll current = dq.front();
        // Found B
        if (current == B) {
            foundB = true;
            break;
        }
        dq.pop_front();

        // Check neighbors
        ll x = current.f, y = current.s;
        if (valid(x + 1, y) && step[x + 1][y] == '*' && maze[x + 1][y] != '#') {
            step[x + 1][y] = 'D';
            dq.pb(mp(x + 1, y));
        }
        if (valid(x - 1, y) && step[x - 1][y] == '*' && maze[x - 1][y] != '#') {
            step[x - 1][y] = 'U';
            dq.pb(mp(x - 1, y));
        }
        if (valid(x, y + 1) && step[x][y + 1] == '*' && maze[x][y + 1] != '#') {
            step[x][y + 1] = 'R';
            dq.pb(mp(x, y + 1));
        }
        if (valid(x, y - 1) && step[x][y - 1] == '*' && maze[x][y - 1] != '#') {
            step[x][y - 1] = 'L';
            dq.pb(mp(x, y - 1));
        }
    }

    f0r(i, n) {
        DEBUG(step[i]);
    }

    // Reverse engineer the maze steps 
    vector<char> ret;
    
    pll curr = B;

    ll counter = 0;
    while(foundB && curr != A) {
        char curr_step = step[curr.f][curr.s];
        ret.pb(curr_step);
        
        if (curr_step == 'U') {
            curr.f = curr.f + 1;
        } else if (curr_step == 'D') {
            curr.f = curr.f - 1;
        } else if (curr_step == 'L') {
            curr.s = curr.s + 1;
        } else if (curr_step == 'R') {
            curr.s = curr.s - 1;
        }
    }
    reverse(ret.begin(), ret.end());
    DEBUG(ret);

    if (foundB) {
        cout << "YES" << endl << ret.size() << endl;
        f0r(i, ret.size()) {
            cout << ret[i];
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }
}

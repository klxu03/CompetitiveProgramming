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

ll q, Q, T, k, l, r, x, y, z, g;
int n, m;

vector<vector<bool>> visited;
vector<string> inp;

bool isValid(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < m;
}

void floodfill(pll start) {
	deque<pll > dq; // [row #, col #]
	dq.push_back(start);
    visited[start.f][start.s] = true;

    vector<int> dr = {1, -1, 0, 0};
    vector<int> dc = {0, 0, 1, -1};

	while(!dq.empty()) {
		pll current = dq.front();
        dq.pop_front();

        f0r(i, 4) {
            int newR = current.f + dr[i];
            int newC = current.s + dc[i];
            if (isValid(newR, newC) && !visited[newR][newC] && inp[newR][newC] == '.') {
                visited[current.f + dr[i]][current.s + dc[i]] = true;
                dq.pb(mp(current.f + dr[i], current.s + dc[i]));
            }
        }
        DEBUG(start, current);
	}
}

//Problem URL: https://cses.fi/problemset/task/1192 
int main() {
    io;
    cin >> n >> m;

    inp = vector<string>(n);
    visited = vector<vector<bool>>(n, vector<bool>(m, false));

    f0r(i, n) {
        cin >> inp[i];
    }

    int counter = 0;
    f0r(i, n) {
        f0r(j, m) {
            if (visited[i][j] == false && inp[i][j] == '.') {
                floodfill(mp(i, j));
                counter++;
            }
        }
    }

    cout << counter << endl;
}

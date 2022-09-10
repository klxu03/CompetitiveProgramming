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
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

void usacio(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
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

ll q, Q, T, l, x, y, z, g;
ll n, k, r;

// vector<vector<vector<vector<bool>>>> isRoad;
const int MAX_N = 100;
bool isRoad[MAX_N][MAX_N][MAX_N][MAX_N];
bool cowExists[MAX_N][MAX_N];

bool isValid(int from_r, int from_c, int to_r, int to_c) {
    return to_r >= 0 && to_r < n && to_c >= 0 && to_c < n 
    && !isRoad[from_r][from_c][to_r][to_c]
    && from_r >= 0 && from_r < n && from_c >= 0 && from_c < n;
}

int floodfill(pll start) {
    DEBUG("start floodfill");
	/* Create these two global variables */
	vector<vector<bool> > visited(n, vector<bool>(n, false));
    DEBUG("made visited array");

	deque<pll > dq; // [row #, col #]
	dq.push_back(start);
    DEBUG("initialized 1");
    DEBUG(start.f, start.s);
    visited[start.f][start.s] = true;
    DEBUG("initialized 2");

    vector<int> dr = {1, -1, 0, 0};
    vector<int> dc = {0, 0, 1, -1};
    int ret = 0; // num of cows this floodfill has seen

    DEBUG("before while");
	while(!dq.empty()) {
		pll current = dq.front();
        dq.pop_front();

        f0r(i, 4) {
            int newR = current.f + dr[i];
            int newC = current.s + dc[i];

            if (isValid(current.f, current.s, newR, newC) && !visited[newR][newC]) {
                visited[newR][newC] = true;
                dq.pb(mp(newR, newC));
                if (cowExists[newR][newC]) {
                    ret++;
                }
            }
        }
	}

    return k - ret - 1; // - 1 because pair with self
}

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=716
int main() {
    usaco("countcross");
	// usacio("testCase");
    // io;
    cin >> n >> k >> r;

    vector<array<pll, 2>> roads(r); 
    vector<pll> cows(k);

    f0r(i, r) {
        ll r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        r1--; c1--; r2--; c2--;
        roads[i] = {mp(r1, c1), mp(r2, c2)};
        isRoad[r1][c1][r2][c2] = true;
        isRoad[r2][c2][r1][c1] = true;
    }

    f0r(i, k) {
        ll r, c;
        cin >> r >> c;
        r--; c--;
        cows[i] = mp(r, c);
        cowExists[r][c] = true;
    }

    int counter = 0;
    DEBUG("before for");
    f0r(i, cows.size()) {
        counter += floodfill(cows[i]);
        DEBUG(i);
    }

    cout << counter/2 << endl;
}

#include <bits/stdc++.h>

using namespace std;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = c - 1; a >= b; a--)
#define pb push_back
#define f first
#define s second
using ll = long long;

#define mp make_pair
#define t third
#define pll pair<ll, ll>
#define pii pair<int, int>

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

/* Variartic Macros and Functions so max(a, b, c, d, ... z) works out of box */
template<typename T> constexpr const inline T& _max(const T& x, const T& y) {return x<y?y:x;}
template<typename T> constexpr const inline T& _min(const T& x, const T& y) {return x<y?x:y;}
template<typename T,typename ...S>constexpr const inline T& _max(const T& m, const S&...s){return _max(m,_max(s...));}
template<typename T,typename ...S>constexpr const inline T& _min(const T& m, const S&...s){return _min(m,_min(s...));}
#define max(...) _max(__VA_ARGS__)
#define min(...) _min(__VA_ARGS__)

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
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

ll q, Q, T, k, l, r, x, y, z;
int n, m;

void solve(); 

// Problem URL: 
int main() {
	io;
	long long test_cases = 1;
	// cin >> test_cases;
	
    for (int i = 0; i < test_cases; i++) {
		solve();
    }
}

class DSU {
    public:
    vector<int> c; // c for components

    DSU() {
        // c = vector<int>(n, -1);
    }

    void init(int n) {
      c = vector<int>(n, -1);
    }

    // get representive component (uses path compression)
	  int get(int x) { 
        return c[x] < 0 ? x : c[x] = get(c[x]); 
    }

    bool same_set(int a, int b) { 
        return get(a) == get(b); 
    }

    int size(int x) { 
        return -c[get(x)]; 
    }

    bool unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return false; // same group
		if (c[x] > c[y]) swap(x, y); // if c[x] is less negative, or greater than c[y]
		
        c[x] += c[y]; 
        c[y] = x;
		return true;
	}
};

DSU groups;

vector<string> maze;
map<int, int> ma; // character to # of dots eaten

bool is_valid(int y, int x) {
  return y >= 0 && y < n && x >= 0 && x < m;
}

// orig representing their group
void floodfill(int y, int x, int orig) {
  vector<int> dx = {-1, 1, 0, 0};
  vector<int> dy = {0, 0, -1, 1};

  deque<pii> dq;
  dq.pb({y, x});

  vector<vector<bool>> visited(n, vector<bool>(m, false));
  visited[y][x] = true;

  ll ate = 0;

  while (!dq.empty()) {
    pii curr = dq.front();
    dq.pop_front();

    f0r(i, 4) {
      int new_x = curr.s + dx[i];
      int new_y = curr.f + dy[i];
      if (!is_valid(new_y, new_x)) {
        continue;
      }

      if (visited[new_y][new_x] && maze[new_y][new_x] >= 'A' && maze[new_y][new_x] <= 'W') {
        if ((maze[curr.f][curr.s] >= 'A' && maze[curr.f][curr.s] <= 'W')) {
          continue;
        }

        // groups.unite(orig, maze[new_y][new_x] - 'A');
        // continue;
      } else if (visited[new_y][new_x]) {
        continue;
      }

      visited[new_y][new_x] = true;

      if (maze[new_y][new_x] == '.') {
        ate++;
        dq.pb({new_y, new_x});
      } else if (maze[new_y][new_x] == ' ') {
        dq.pb({new_y, new_x});
      } else if (maze[new_y][new_x] < 'X') { // letter
        // DEBUG("uniting", orig, maze[new_y][new_x]);
        if (maze[curr.f][curr.s] >= 'A' && maze[curr.f][curr.s] <= 'W') {
          // current is a door
        } else {
          // can go ahead and move into this space as previous not a door, and non doors can move to doors
          dq.pb({new_y, new_x});
          groups.unite(orig, (int) (m*new_y + new_x));
        }
      }
    }
  }

  ma[orig] = ate;
}

void solve() {
	cin >> n >> m;
  maze = vector<string>(n);

  cin.ignore();
  f0r(i, n) {
    getline(cin, maze[i]);
  }

  groups.init(n * m); // at most 26 letters

  ll total = 0;
  // each character door - 'A' is their DSU group
  f0r(i, n) {
    f0r(j, m) {
      if (maze[i][j] >= 'A' && maze[i][j] <= 'W') {
        // new letter 
        if (groups.get(m*i + j) == (m*i + j)) {
          floodfill(i, j, m*i + j);
        }
      } else if (maze[i][j] == '.') {
        total++;
      }
    }
  }


  DEBUG(groups.c);
  DEBUG(ma, total);

  ll num_letters = 0;
  for (pair<int, int> p : ma) {
    total -= p.second;
    
    if (p.s > 0) {
      num_letters++;
    }
  }

  cout << num_letters << " " << total << endl;
}
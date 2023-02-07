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

DSU its_dsu;

class UnweightedGraph {
	public:
	long long nodes; // # of nodes
	long long edges; // # of edges
	bool undirected;
	vector<vector<long long> > adj; // adjacency neighbor vector
	vector<long long> visited; // visited nodes

  vector<int> prev;
  vector<bool> cyc_visited;

	UnweightedGraph(long long nodes, long long edges, bool undirected) {
		this->nodes = nodes;
		this->edges = edges;
		this->undirected = undirected;
		adj = vector<vector<long long> >(nodes);
		visited = vector<long long>(nodes, -1);

    prev = vector<int>(nodes, -1);
    cyc_visited = vector<bool>(nodes, false);
	}

  vector<pii> cycles;
  int seen = 0;
  map<int, int> cyc_len; // key is it (id) of cycle, val is cycle len
  map<int, int> node_to_it; // key is node, val is it

  map<int, int> acc_node_to_it; // accurate node to it

  // it stands for iteration cycle. if discover already visited node in same iteration, cycle here
  void find_all_cycles(int node, int it) {
    node_to_it[node] = it;
    int neighbor = adj[node][0];
    seen++;
    prev[neighbor] = node;
    if (visited[neighbor] == it) {
      cycles.pb({node, neighbor});  
    } else if (visited[neighbor] == -1) {
      visited[neighbor] = it;
      find_all_cycles(neighbor, it);
    } else {
      its_dsu.unite(it, visited[neighbor]);
      // m[it] = visited[neighbor];
    }
  }

  // unused
  void update_node_to_it() {
    for (auto p : node_to_it) {
      acc_node_to_it[p.f] = its_dsu.get(p.s);
    }
  }

  
  int get_cyc_len(int node, int sz) {
    int neighbor = adj[node][0];
    if (cyc_visited[neighbor]) {
      return sz; 
    } else {
      cyc_visited[neighbor] = true;
      return get_cyc_len(neighbor, sz + 1);
    }
  }
};

const ll modulo = 1e9 + 7;

void solve() {
	cin >> n;

  its_dsu.init(n);

  UnweightedGraph g(n, n, false);
  vector<vector<ll>> adj(n, vector<ll>(1));
  f0r(i, n) {
    int next;
    cin >> next;
    adj[i][0] = next - 1;
  }
  g.adj = adj;

  int curr_node = 0;
  int curr_it = 0;
  while (g.seen < n) {
    g.visited[curr_node] = curr_it;
    g.find_all_cycles(curr_node, curr_it);

    curr_it++;
    for (int i = curr_node + 1; i < n; i++) {
      if (g.visited[i] == -1) {
        curr_node = i;
        break;
      }
    }
  }

  g.update_node_to_it();

  DEBUG(g.cycles);

  DEBUG(g.visited);
  DEBUG(g.prev);
  DEBUG(g.node_to_it);

  f0r(i, n) {
    g.visited[i] = its_dsu.get(g.visited[i]);
  }

  DEBUG(g.visited);

  for (auto p : g.cycles) {
    g.cyc_len[g.visited[p.f]] = g.get_cyc_len(p.f, 0);
  }

  DEBUG(g.cyc_len);

  vector<ll> multiples;
  map<int, int> it_size; // key is iterator, value is size or # of eles
  set<int> its;
  for (int i = 0; i < n; i++) {
    it_size[g.visited[i]]++;
    its.insert(g.visited[i]);
  }

  DEBUG(it_size);

  for (auto it : its) {
    DEBUG(it, it_size[it], g.cyc_len[it]);
    multiples.pb(it_size[it] - g.cyc_len[it] + 2);
  }
  DEBUG(multiples);

  // if (multiples.size() == 0) {
  //   cout << 0 << endl;
  //   return;
  // }

  ll ret = 1;
  f0r(i, multiples.size()) {
    ret = (ret * multiples[i]) % modulo;
  }

  DEBUG(g.adj);
  if (ret == 0) {
    cout << modulo - 1 << endl;
  } else {
    cout << ret - 1 << endl;
  }
}
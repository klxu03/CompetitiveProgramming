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

// Overriding `min` and `max` to support multiple arguments
template<typename T> constexpr const inline T& _max(const T& x, const T& y) {return x<y?y:x;}
template<typename T> constexpr const inline T& _min(const T& x, const T& y) {return x<y?x:y;}
template<typename T,typename ...S>constexpr const inline T& _max(const T& m, const S&...s){return _max(m,_max(s...));}
template<typename T,typename ...S>constexpr const inline T& _min(const T& m, const S&...s){return _min(m,_min(s...));}
#define max(...) _max(__VA_ARGS__)
#define min(...) _min(__VA_ARGS__)

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

struct scc {
  vector<vector<int> > edges, redges;
  vector<bool> used;
  vector<int> order, component;
  int n;

  void init(int _n) {
    n = _n;
    edges = vector<vector<int> >(n);
    redges = vector<vector<int> >(n);
    order.clear();
    component.clear();
  }

  void edge(int u, int v) {
    edges[u].push_back(v);
    redges[v].push_back(u);
  }

  void dfs1(int v) {
    used[v] = true;
    for (int i = 0; i < edges[v].size(); i++) {
      if (!used[edges[v][i]]) {
        dfs1(edges[v][i]);
      }
    }
    order.push_back(v);
  }

  void dfs2(int v) {
    used[v] = true;
    component.push_back(v);
    for (int i = 0; i < redges[v].size(); i++) {
      if (!used[redges[v][i]]) {
        dfs2(redges[v][i]);
      }
    }
  }

  vector<vector<int> > run() {
    vector<vector<int> > components;
    used.assign(n, false);
    for (int i = 0; i < n; i++) {
      if (!used[i]) {
        dfs1(i);
      }
    }

    used.assign(n, false);
    for (int i = 0; i < n; i++) {
      int v = order[n - 1 - i];
      if (!used[v]) {
        dfs2(v);
        components.push_back(component);
        component.clear();
      }
    }

    return components;
  }
};

void solve() {
	cin >> n;
    map<string, vector<string>> m; // key is person's name, value is vector of langs spoken
    
    vector<string> inp(n);
    cin.ignore();
    f0r(i, n) {
        getline(cin, inp[i]);
    }

    set<string> languages;

    int id = 0;
    map<string, int> person_to_id;
    
    f0r(i, n) {
        stringstream ss;
        ss << inp[i];

        string person;
        vector<string> langs;

        ss >> person;
        person_to_id[person] = id;
        while (!ss.eof()) {
            string new_lang;
            ss >> new_lang;
            languages.insert(new_lang);
            langs.pb(new_lang);
        }

        m[person] = langs;
        id++;
    }

    map<string, int> lang_to_id;

    for (auto lang : languages) {
        lang_to_id[lang] = id;
        id++;
    }

    // DEBUG(m);
    // DEBUG(languages);

    vector<vector<int>> big_adj(id); // includes people and languages

    for (pair<string, vector<string>> p : m) {
        big_adj[person_to_id[p.first]].pb(lang_to_id[p.second[0]]);
        big_adj[lang_to_id[p.second[0]]].pb(person_to_id[p.first]);
        f1r(i, 1, p.second.size()) {
            big_adj[lang_to_id[p.second[i]]].pb(person_to_id[p.f]);
        }
    }

    vector<vector<int>> adj(n); // just people now, direct
    for (pair<string, int> p : person_to_id) {
        int lang = big_adj[p.second][0]; // language id this person speaks

        for (int neighbor : big_adj[lang]) {
            adj[p.second].pb(neighbor);
        }
    }

    scc colin_is_smart;
    colin_is_smart.init(n);
    f0r(i, n) {
        for (int neighbor: adj[i]) {
            colin_is_smart.edge(i, neighbor);
        }
    }

    vector<vector<int>> comps = colin_is_smart.run();

    int max_size = 0;
    for (vector<int> comp : comps) {
        max_size = max(max_size, (int) comp.size(), 0);
    }

    cout << n - max_size << endl;
}
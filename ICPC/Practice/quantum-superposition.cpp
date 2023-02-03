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
int n1, n2, m1, m2;

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

class UnweightedGraph {
	public:
	long long nodes; // # of nodes
	long long edges; // # of edges
	bool undirected;
	vector<vector<long long> > adj; // adjacency neighbor vector
	vector<long long> visited; // visited nodes

    vector<ll> indegree;
    vector<set<ll>> poss_lengths; // possible lengths from start to here

	UnweightedGraph(long long nodes, long long edges, bool undirected) {
		this->nodes = nodes;
		this->edges = edges;
		this->undirected = undirected;
		adj = vector<vector<long long> >(nodes);
		visited = vector<long long>(nodes, false);
        indegree = vector<ll>(nodes, 0);
        poss_lengths = vector<set<ll>>(nodes);
	}

	void init_adj() {
		f0r(i, edges) {
			ll n1, n2; // n1 for node1
			cin >> n1 >> n2;
			adj[n1 - 1].pb(n2 - 1);
            indegree[n2 - 1]++;
			if(undirected) {
				adj[n2 - 1].pb(n1 - 1);
			}
		}
	}

    // note that starting_node is unnecessary since indegree 0
    // create an indegree vector 
    void toposort(long long starting_node) {
        deque<long long> dq;
        dq.push_back(starting_node);

        for (int i = 0; i < nodes; i++) {
            if (i == starting_node) continue;

            if (indegree[i] == 0) {
                dq.pb(i);
            }
        }
        poss_lengths[0].insert(0);

        while(!dq.empty()) {
            long long current = dq.front();
            dq.pop_front();

            for (long long neighbor : adj[current]) {
                indegree[neighbor]--;
                for (auto len : poss_lengths[current]) {
                    poss_lengths[neighbor].insert(len + 1);
                }

                if (indegree[neighbor] == 0) {
                    dq.push_back(neighbor);
                }
            }
        }
    }
};

void solve() {
	cin >> n1 >> n2 >> m1 >> m2;
    UnweightedGraph u1(n1, m1, false);
    UnweightedGraph u2(n2, m2, false);

    u1.init_adj();
    u2.init_adj();

    cin >> q;
    vector<int> queries(q);
    f0r(i, q) {
        cin >> queries[i];
    }

    u1.toposort(0);
    u2.toposort(0);

    DEBUG(u1.poss_lengths[n1 - 1]);
    DEBUG(u2.poss_lengths[n2 - 1]);

    f0r(i, q) {
        int curr = queries[i];

        bool possible = false;
        for (auto len : u1.poss_lengths[n1 - 1]) {
            if (u2.poss_lengths[n2 - 1].count(curr - len) == 1) {
                possible = true;
                break;
            }
        }

        // if (possible) {
        //     cout << "Yes" << endl;
        //     continue;
        // } else {
        //     for (auto len : u2.poss_lengths[n2 - 1]) {
        //         if (u1.poss_lengths[n1 - 1].count(curr - len) == 1) {
        //             possible = true;
        //             break;
        //         }
        //     }
        // }

        if (possible) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}
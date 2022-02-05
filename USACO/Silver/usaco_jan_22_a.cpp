#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <functional>
#include <array>
#include <deque>
#include <climits>

#include <math.h>

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

ll n, q, Q, T, k, l, r, x, y, z, g;

//Problem URL: 
int main() {
    io;
	cin >> n;
	f0r(i, n) {
		ll first, second;
		cin >> first >> second;

		ll double_counter = 0;
		while(first * 2 <= second) {
			first *= 2;
			double_counter++;
		}

		ll div_2_counter = 0;
		while(first > second) {
			if (first % 2 == 1) {
				first++;
				div_2_counter++;
			}
			first /= 2;
			div_2_counter++;
		} 
		if(first % 2 == 1 && first != second) {
			first++;
			div_2_counter++;
		}

		// now we have first < second
		DEBUG(first, second);
		vector<pair<ll, ll> > combos;
		ll diff = second - first;

		combos.pb(mp(diff, 0));
		ll num_divisions = 0;

		while(diff >= 2) {
			ll new_counter = combos[num_divisions].s;

			if(first % 2 == 1) {
				first++;
				new_counter++;
			}

			first /= 2;
			new_counter += 2;
			num_divisions++;

			if(diff % 2 == 1) new_counter++;
			diff /= 2;

			combos.pb(mp(diff, new_counter));
			DEBUG(second, first, diff, new_counter);
		}
			
		DEBUG(combos);
		DEBUG(div_2_counter);

		ll min = combos[0].f + combos[0].s + div_2_counter;
		f1r(i, double_counter, num_divisions) {
			ll new_min = combos[i].f + combos[i].s + div_2_counter;
			if (new_min < min) {
				min = new_min;
			}
		}
		cout << min - double_counter << endl;
	}

}
class Graph {
	public:
	ll n; // # of nodes
	ll e; // # of edges
	bool undirected;
	vector<vector<ll> > adj; // adjacency neighbor vector
	vector<bool> visited; // visited nodes

	Graph(ll nodes, ll edges, bool undirected) {
		n = nodes;
		e = edges;
		this->undirected = undirected;
		adj = vector<vector<ll> >(n);
		visited = vector<bool>(n);
	}

    void add_adj(vector<vector<ll> > &adj) {
        this->adj = adj;
    }

	void init_adj() {
		f0r(i, e) {
			ll n1, n2; // n1 for node1
			cin >> n1 >> n2;
			adj[n1 - 1].pb(n2 - 1);
			if(undirected) {
				adj[n2 - 1].pb(n1 - 1);
			}
		}
	}

	void display() {
		DEBUG("[");
		f0r(i, n) {
			DEBUG(i, adj[i]);
		}
		DEBUG("]");
	}

	void dfs(ll starting_node) {
		deque<int> dq;
		dq.push_front(starting_node);
		visited[starting_node] = true;
		DEBUG(visited, starting_node, adj[starting_node]);

		while(!dq.empty()) {
			ll current = dq.front();
			visited[current] = true;
			// DEBUG(current, dq, visited);

			if(adj[current].size() == 0) {
				dq.pop_front();
			}

			f0r(i, adj[current].size()) {
				ll neighbor = adj[current][i];
				// DEBUG(i, neighbor);
				if(visited[neighbor] == false) {
					dq.push_front(neighbor);
					break;
				} 
				/* If I've skipped through all and none of 
				the neighbors haven't been visited */
				if (i == adj[current].size() - 1) dq.pop_front();
			}
		}
	}

};

ll binary_search(ll lo, ll hi, bool works) {
	ll mid = (lo + hi + 1)/2;

	// Binary search part
	DEBUG(lo, hi, mid, works);
	if(works) {
		if(hi == mid) {
			hi--;
		} else {
			hi = mid;
		}
	} else {
		lo = mid;
	}
}
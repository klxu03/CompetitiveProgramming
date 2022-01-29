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

		if(first <= second) {
			ll counter = 0;
			if(first != second && first % 2 == 1) {
				first++;
				counter++;
			}

			ll diff;
			ll multiply_2 = 0;
			if (second/first > 1) {
				while(first * 2 < second) {
					first *= 2;
					multiply_2++;
				}
				diff = second - first;
				// calculate diff
			} else {
				diff = second - first;
			}
			
			DEBUG(second, first, diff, counter);
			ll div_counter = 0;
			ll new_diff = diff;
			ll odd_count = 0;
			DEBUG(ceil((double) new_diff/2));
			while(ceil((double) new_diff/2) >= 2) {
				DEBUG("in while");
				first /= 2;
				if(new_diff % 2 == 1) odd_count++;
				new_diff /= 2;
				div_counter++;
				DEBUG(first, new_diff);
			}
			DEBUG(second, first, new_diff, div_counter, counter, odd_count, multiply_2);

			cout << new_diff + div_counter * 2 + counter + odd_count - multiply_2 << endl;
		} else {
			ll counter = 0;
			while(first > second) {
				DEBUG("first/2", first, second, counter);
				if(first % 2 == 1) {
					first++;
					counter++;
				}
				first /= 2;
				counter++;
			} // now we have first < second
			
			if(first != second && first % 2 == 1) {
				first++;
				counter++;
			}

			ll diff = second - first;
			
			DEBUG(second, first, diff, counter);
			ll div_counter = 0;
			ll new_diff = diff;
			ll odd_count = 0;
			while(new_diff/2 > 2) {
				first /= 2;
				if(new_diff % 2 == 1) odd_count++;
				new_diff /= 2;
				div_counter++;
				DEBUG(first, new_diff);
			}
			DEBUG(second, first, new_diff, div_counter, counter);

			cout << new_diff + div_counter * 2 + counter + odd_count << endl;
		}

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
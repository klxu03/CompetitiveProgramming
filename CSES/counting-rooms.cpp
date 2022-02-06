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

void solve(); 

// Problem: https://cses.fi/problemset/task/1192
int main() {
	io;
	ll test_cases = 1;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

vector<string> maze;
vector<vector<bool> > visited;

void floodfill(pll start) {
	deque<pll > dq;
	dq.push_back(start);

	while(!dq.empty()) {
		pll current = dq.front();
		DEBUG(current, dq);
		visited[current.f][current.s] = true;

		if (current.f - 1 >= 0 && visited[current.f - 1][current.s] == false && maze[current.f - 1][current.s] == '.') {
			// Top
			dq.push_front(mp(current.f - 1, current.s));
		} else if (current.s + 1 <= m - 1 && visited[current.f][current.s + 1] == false && maze[current.f][current.s + 1] == '.') {
			// Right
			dq.push_front(mp(current.f, current.s + 1));
		} else if (current.f + 1 <= n - 1 && visited[current.f + 1][current.s] == false && maze[current.f + 1][current.s] == '.') {
			// Bottom
			dq.push_front(mp(current.f + 1, current.s));
		} else if (current.s - 1 >= 0 && visited[current.f][current.s - 1] == false && maze[current.f][current.s - 1] == '.') {
			// Left
				dq.push_front(mp(current.f, current.s - 1));
		} else {
			dq.pop_front();
		}
	}
}

void solve() {
	cin >> n >> m;

	maze = vector<string>(n);
	visited = vector<vector<bool> >(n, vector<bool>(m, false));
	f0r(i, n) {
		cin >> maze[i];
	}

	DEBUG(maze);
	DEBUG(visited);

	ll counter = 0;
	f0r(i, n) {
		f0r(j, m) {
			if(visited[i][j] == false) {
				if (maze[i][j] == '.') {
					floodfill(mp(i, j));
					counter++;
				}
			}
		}
	}

	DEBUG(visited);
	cout << counter << endl;
}
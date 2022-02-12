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
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

ll n, m, q, Q, T, k, l, r, x, y, z, g;

ll binary_search(ll &lo, ll &hi, bool works) {
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
		lo = mid + 1;
	}
}

vector<vector<bool> > visited;
vector<vector<ll> > inp;

void reset_visited() {
	f0r(i, n) {
		f0r(j, m) {
			visited[i][j] = false;
		}
	}
}

void floodfill(pll start, ll amt) {
	/* Create these two global variables */

	deque<pll > dq;
	dq.push_back(start);

	while(!dq.empty()) {
		pll current = dq.front();
		// if (amt == 15) {
		// 	cout << "------" << endl;
		// 	f0r(i, n) {
		// 		f0r(j, m) {
		// 			cout << visited[i][j] << " ";
		// 		}
		// 		cout << endl;
		// 	}
		// }
		visited[current.f][current.s] = true;
		ll current_amt = inp[current.f][current.s];

		if (current.f - 1 >= 0 && visited[current.f - 1][current.s] == false && abs(inp[current.f - 1][current.s] - current_amt) <= amt) {
			// Top
			dq.push_front(mp(current.f - 1, current.s));
		} else if (current.s + 1 <= m - 1 && visited[current.f][current.s + 1] == false && abs(inp[current.f][current.s + 1] - current_amt) <= amt) {
			// Right
			dq.push_front(mp(current.f, current.s + 1));
		} else if (current.f + 1 <= n - 1 && visited[current.f + 1][current.s] == false && abs(inp[current.f + 1][current.s] - current_amt) <= amt) {
			// Bottom
			dq.push_front(mp(current.f + 1, current.s));
		} else if (current.s - 1 >= 0 && visited[current.f][current.s - 1] == false && abs(inp[current.f][current.s - 1] - current_amt) <= amt) {
			// Left
			dq.push_front(mp(current.f, current.s - 1));
		} else {
			dq.pop_front();
		}
	}
}

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=740
int main() {
	/*
	Brute force go through each cell, and then go expand right as much as possible
	if expansion is possible, mark it as visited in the 2D array
	Then expand right, all the way
	Then expand down, all the way
	Mark +1 in counter

	And then keep going through the for loop until you can find a non-visited cell
	Then go ahead and expand left as much as possible
	And then right from the leftmost
	Then down
	Then mark +1 in counter

	And repeat
	*/
    // usaco("where");
    io;
	cin >> n;
	vector<string> inp(n);
	f0r(i, n) {
		cin >> inp[i];
	}

	vector<vector<bool> > visited(n, vector<bool>(n, false));
	ll counter = 0;
	f0r(i, n) {
		f0r(j, n) {
			if (visited[i][j] == false) {
				visited[i][j] = true;
				char c1 = inp[i][j];
				// keep going left until it hits edge and the color changes

				// then go right if it uses the same two colors
				// now go up
				// now go down
			}
		}
	}

}

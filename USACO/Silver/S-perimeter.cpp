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

vector<string> ice;
vector<vector<bool> > visited;

pll floodfill(pll start) {
	deque<pll > dq;
	dq.push_back(start);

	ll area = 0;
	ll perimeter = 0;

	while(!dq.empty()) {
		pll current = dq.front();
		DEBUG(current, dq);
		visited[current.f][current.s] = true;

		if (current.f - 1 >= 0 && visited[current.f - 1][current.s] == false && ice[current.f - 1][current.s] == '#') {
			// Top
			dq.push_front(mp(current.f - 1, current.s));
		} else if (current.s + 1 <= n - 1 && visited[current.f][current.s + 1] == false && ice[current.f][current.s + 1] == '#') {
			// Right
			dq.push_front(mp(current.f, current.s + 1));
		} else if (current.f + 1 <= n - 1 && visited[current.f + 1][current.s] == false && ice[current.f + 1][current.s] == '#') {
			// Bottom
			dq.push_front(mp(current.f + 1, current.s));
		} else if (current.s - 1 >= 0 && visited[current.f][current.s - 1] == false && ice[current.f][current.s - 1] == '#') {
			// Left
			dq.push_front(mp(current.f, current.s - 1));
		} else {
			dq.pop_front();
			area++;

			// Top
			if (current.f - 1 >= 0 && ice[current.f - 1][current.s] == '.') {
				perimeter++;
			} else if (current.f - 1 < 0) {
				perimeter++;
			}

			// Right
			if (current.s + 1 <= n - 1 && ice[current.f][current.s + 1] == '.') {
				perimeter++;
			} else if (current.s + 1 > n - 1) {
				perimeter++;
			}

			// Bottom
			if (current.f + 1 <= n - 1 && ice[current.f + 1][current.s] == '.') {
				perimeter++;
			} else if (current.f + 1 > n - 1) {
				perimeter++;
			}

			// Left
			if (current.s - 1 >= 0 && ice[current.f][current.s - 1] == '.') {
				perimeter++;
			} else if (current.s - 1 < 0) {
				perimeter++;
			}
		}
	}

	return mp(area, perimeter);
}

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=895
int main() {
    usaco("perimeter");
    // io;

	cin >> n;

	ice = vector<string>(n);
	visited = vector<vector<bool> >(n, vector<bool>(n, false));
	f0r(i, n) {
		cin >> ice[i];
	}

	DEBUG(ice);
	DEBUG(visited);

	ll area = -1;
	ll per = 0;

	f0r(i, n) {
		f0r(j, n) {
			if(visited[i][j] == false) {
				if (ice[i][j] == '#') {
					pll ret = floodfill(mp(i, j));
					if (ret.f > area) {
						area = ret.f;
						per = ret.s;
					} else if (ret.f == area) {
						per = min(per, ret.s);
					}
				}
			}
		}
	}

	DEBUG(visited);
	cout << area << " " << per << endl;

	// ll perimeter = 0;
	// pll current = mp(5, 5);
	// // Top
	// if (current.f - 1 >= 0 && ice[current.f - 1][current.s] == '.') {
	// 	perimeter++;
	// } else if (current.f - 1 < 0) {
	// 	perimeter++;
	// }

	// // Right
	// if (current.s + 1 <= n - 1 && ice[current.f][current.s + 1] == '.') {
	// 	perimeter++;
	// } else if (current.s + 1 > n - 1) {
	// 	perimeter++;
	// }

	// // Bottom
	// if (current.f + 1 <= n - 1 && ice[current.f + 1][current.s] == '.') {
	// 	perimeter++;
	// } else if (current.f + 1 > n - 1) {
	// 	perimeter++;
	// }

	// // Left
	// if (current.s - 1 >= 0 && ice[current.f][current.s - 1] == '.') {
	// 	perimeter++;
	// } else if (current.s - 1 < 0) {
	// 	perimeter++;
	// }
	// DEBUG(perimeter);

}
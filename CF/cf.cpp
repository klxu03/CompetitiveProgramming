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

ll n, m, q, Q, T, k, l, r, x, y, z, g;

void solve(); 

// Problem: https://codeforces.com/contest/1722/problem/E
int main() {
	io;
	ll test_cases = 1;
	cin >> test_cases;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

bool isValid(int r, int c) {
	return r >= 0 && r < n && c >= 0 && c < m;
}

void solve() {
	cin >> n >> m;
	vector<vector<string>> inp(n, vector<string>(m));
	vector<vector<int>> dsu(n, vector<int>(m, -1));

	f0r(i, n) {
		string s;
		cin >> s;
		f0r(j, m) {
			string ret = "";
			ret += s[j];
			inp[i][j] = ret;
		}
	}

	f0r(i, n) {
		DEBUG(inp[i]);
	}

	vector<vector<pll>> L_checks = {
		{{1, 0}, {1, 1}},
		{{1, 0}, {0, 1}},
		{{0, 1}, {1, 1}},
		{{1, 0}, {1, -1}}
	};

	vector<pll> neighbor_checks = {
		{-1, -1},
		{-1, 0},
		{-1, 1},
		{0, -1},
		{0, 1},
		{1, -1},
		{1, 0},
		{1, 1}
	};

	int counter = 1;
	f0r(i, n) {
		f0r(j, m) {
			if (inp[i][j] != ".") {
				// Go make this unvisited piece a rectangle
				if (inp[i][j] == "*" && dsu[i][j] == -1) {
					// Go through the 4 possible rectangles and check if valid
					bool isRect = true;
					f0r(k, 4) {
						vector<pll> currL = L_checks[k];
						isRect = true;
						f0r(l, 2) {
							int newR = i + currL[l].f;
							int newC = j + currL[l].s;

							if (!(isValid(newR, newC) && inp[newR][newC] == "*" && dsu[newR][newC] == -1)) {
								DEBUG(newR, newC, isValid(newR, newC));
								if (isValid(newR, newC)) {
									DEBUG(inp[newR][newC]);
								}

								isRect = false;
							}
						}

						if (isRect) {
							dsu[i][j] = counter;
							DEBUG("isRect true, making rectangle", inp[i][j]);
							f0r(l, 2) {
								int newR = i + currL[l].f;
								int newC = j + currL[l].s;

								dsu[newR][newC] = counter;
							}
							counter++;
							
							break;
						}
					}

					// This stranded '*' turned isRect false so not a rectangle on any
					if (!isRect) {
						DEBUG("isRect");
						cout << "NO" << endl;
						return;
					}
				}

				// Check if this rect has any other rect in the neighborhood
				int curr = dsu[i][j];
				f0r(k, 8) {
					int newR = i + neighbor_checks[k].f;
					int newC = j + neighbor_checks[k].s;

					if (isValid(newR, newC) && inp[newR][newC] != "." && curr != dsu[newR][newC]) {
						DEBUG("encroaching neighbor", curr, dsu[newR][newC]);
						cout << "NO" << endl;
						return;
					}
				}

			}
		}
	}

	cout << "YES" << endl;
}
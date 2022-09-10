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
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

ll m, q, Q, T, k, l, r, x, y, z, g;
int n;
vector<string> inp;

bool isValid(int x, int y) {
	bool ret = true;
	ret = x >= 0 && x < n && y >= 0 && y < n;
	ret = ret && inp[x][y] != 'H';

	return ret;
}

// Conduct Bessie moving forward maneuver on both cows
array<int, 6> moveForward(array<int, 6>& current) {
	array<int, 6> ret;
	f0r(i, 6) {
		ret[i] = current[i];
	}

	// Don't go forward if already in the top right corner
	// Cannot go into a H
	// Cannot go past world borders
	// One cow can not move but the other will

	// Cow 1 is currently not at the top right corner
	if (!(current[0] == 0 && current[1] == n - 1)) {

		// Cow 1 is currently facing up
		if (current[2] == 0) {
			if (isValid(current[0] - 1, current[1])) {
				ret[0] = current[0] - 1;
			}
		}

		// Cow 1 right
		if (current[2] == 1) {
			if (isValid(current[0], current[1] + 1)) {
				ret[1] = current[1] + 1;
			}
		}

		// Cow 1 down
		if (current[2] == 2) {
			if (isValid(current[0] + 1, current[1])) {
				ret[0] = current[0] + 1;
			}
		}

		// Cow 1 left
		if (current[2] == 3) {
			if (isValid(current[0], current[1] - 1)) {
				ret[1] = current[1] - 1;
			}
		}
	}

	if (!(current[3] == 0 && current[4] == n - 1)) {
		// Cow 2 is currently facing up
		if (current[5] == 0) {
			if (isValid(current[3] - 1, current[4])) {
				ret[3] = current[3] - 1;
			}
		}

		// Cow 2 right
		if (current[5] == 1) {
			if (isValid(current[3], current[4] + 1)) {
				ret[4] = current[4] + 1;
			}
		}

		// Cow 2 down
		if (current[5] == 2) {
			if (isValid(current[3] + 1, current[4])) {
				ret[3] = current[3] + 1;
			}
		}

		// Cow 2 left
		if (current[5] == 3) {
			if (isValid(current[3], current[4] - 1)) {
				ret[4] = current[4] - 1;
			}
		}
	}

	return ret;
}

array<int, 6> rotateLeft(array<int, 6>& current) {
	array<int, 6> ret;
	f0r(i, 6) {
		ret[i] = current[i];
	}

	// Cow 1 is currently not at the top right corner
	if (!(current[0] == 0 && current[1] == n - 1)) {
		// Cow 1 is currently facing up
		if (current[2] == 0) {
			ret[2] = 3;
		} else {
			ret[2] = current[2] - 1;
		}
	}

	if (!(current[3] == 0 && current[4] == n - 1)) {
		// Cow 2 is currently facing up
		if (current[5] == 0) {
			ret[5] = 3;
		} else {
			ret[5] = ret[5] - 1;
		}
	}

	return ret;
}

array<int, 6> rotateRight(array<int, 6>& current) {
	array<int, 6> ret;
	f0r(i, 6) {
		ret[i] = current[i];
	}

	// Cow 1 is currently not at the top right corner
	if (!(current[0] == 0 && current[1] == n - 1)) {
		// Cow 1 is currently facing left
		if (current[2] == 3) {
			ret[2] = 0;
		} else {
			ret[2] = current[2] + 1;
		}
	}

	if (!(current[3] == 0 && current[4] == n - 1)) {
		// Cow 2 is currently facing left
		if (current[5] == 3) {
			ret[5] = 0;
		} else {
			ret[5] = ret[5] + 1;
		}
	}

	return ret;
}

//Problem URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=695 
int main() {
    usaco("cownav");
    // io;

	cin >> n;

	// visited[x][y][direction] where for dir, 0 is up, 1 right, 2 down, 3 left
	// then visited[x1][y1][dir1][x2][y2][dir2] marks pair of Bessie being in x1, y1, dir1 and x2, y2, dir2 and the # of moves it took to get there from start
	// x is row, y is col, z is dir
	vector<vector<vector<vector<vector<vector<ll>>>>>> visited(n, vector<vector<vector<vector<vector<ll>>>>>(n, vector<vector<vector<vector<ll>>>>(4, vector<vector<vector<ll>>>(n, vector<vector<ll>>(n, vector<ll>(4, -1)))))); // visited nodes

	inp = vector<string>(n);
	f0r(i, n) {
		cin >> inp[i];
	}

	DEBUG(inp);

	deque<array<int, 6>> dq;
	dq.pb({n - 1, 0, 0, n - 1, 0, 1});
	// Add both mirrors swapping cow1 and cow2
	visited[n - 1][0][0][n - 1][0][1] = 0;
	visited[n - 1][0][1][n - 1][0][0] = 0;

	ll ret = -1;

	while (true) {
		array<int, 6> current = dq.front();
		dq.pop_front();
		ll distance = visited[current[0]][current[1]][current[2]][current[3]][current[4]][current[5]];
		DEBUG(distance, current);
		array<int, 6> postMove;

		// BFS first "neighbor" of going forward
		postMove = moveForward(current);
		if (visited[postMove[0]][postMove[1]][postMove[2]][postMove[3]][postMove[4]][postMove[5]] == -1) {
			dq.pb(postMove);
			visited[postMove[0]][postMove[1]][postMove[2]][postMove[3]][postMove[4]][postMove[5]] = distance + 1;
			visited[postMove[3]][postMove[4]][postMove[5]][postMove[0]][postMove[1]][postMove[2]] = distance + 1;
		}

		// If postMove made both cows to the topRight, trigger finished check
		if (postMove[0] == 0 && postMove[1] == n - 1 && postMove[3] == 0 && postMove[4] == n - 1) {
			DEBUG("solution:", postMove);
			ret = distance + 1;
			break;
		}

		// BFS first "neighbor" of going forward
		postMove = rotateLeft(current);
		if (visited[postMove[0]][postMove[1]][postMove[2]][postMove[3]][postMove[4]][postMove[5]] == -1) {
			dq.pb(postMove);
			visited[postMove[0]][postMove[1]][postMove[2]][postMove[3]][postMove[4]][postMove[5]] = distance + 1;
			visited[postMove[3]][postMove[4]][postMove[5]][postMove[0]][postMove[1]][postMove[2]] = distance + 1;
		}
		
		// BFS first "neighbor" of going forward
		postMove = rotateRight(current);
		if (visited[postMove[0]][postMove[1]][postMove[2]][postMove[3]][postMove[4]][postMove[5]] == -1) {
			dq.pb(postMove);
			visited[postMove[0]][postMove[1]][postMove[2]][postMove[3]][postMove[4]][postMove[5]] = distance + 1;
			visited[postMove[3]][postMove[4]][postMove[5]][postMove[0]][postMove[1]][postMove[2]] = distance + 1;
		}
	}

	cout << ret << endl;
}
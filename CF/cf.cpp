#include <bits/stdc++.h>

using namespace std;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = c - 1; a >= b; a--)
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

ll q, Q, T, k, l, r, x, y, z;
int n, m;

void solve(); 

// Problem: 
int main() {
	io;
	ll test_cases = 1;
	cin >> test_cases;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

vector<char> letters;
// all n choose m permutations : # letters | k
vector<vector<char>> gen_permutations(int n, int m) {
	vector<int> starts(m);

	int sz = 1;
	for (int i = 2; i < n + 1; i++) {
		sz *= i;
	}

	int div1 = 1;
	for (int i = 2; i < m + 1; i++) {
		div1 *= i;
	}

	int div2 = 1;
	for (int i = 2; i < n - m + 1; i++) {
		div2 *= i;
	}
	sz = sz/(div1 * div2);

	vector<vector<char>> ret(sz);
	for (int i = 0; i < m; i++) {
		starts[i] = i;
	}

	for (int i = 0; i < sz; i++) {
		vector<char> curr(m);
		f0r(j, m) {
			curr[j] = letters[starts[j]];
		}
		ret[i] = curr;

		int reset_counter = 0; // # of eles from back u gotta reset
		for (int j = 1; j < m; j++) {
			if (starts[m - j] == n - j) {
				reset_counter++;
			}
		}

		if (reset_counter == 0) {
			starts[m - 1]++;
		} else {
			starts[m - reset_counter - 1]++;

			int add_counter = 1;
			for (int j = m - reset_counter; j < m; j++) {
				starts[j] = starts[m - reset_counter - 1] + add_counter;
				add_counter++;
			}
		}	
	}

	return ret;
}

void solve() {
	cin >> n >> k;
	string a;
	string b;
	letters.clear();

	cin >> a >> b;

	set<char> letters_in_a;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == b[i]) {
			a[i] = 'X';
		} else {
			letters_in_a.insert(a[i]);
		}
	}

	for (auto it : letters_in_a) {
		letters.push_back(it);
	}

	k = min(k, (ll) letters.size());

	ll ret = 0;

	if (k == 0) {
		// sum em up now
		int j = 0;
		ll curr_sum = 0;
		while (j < n) {
			ll curr_add = 0;

			while (a[j] == 'X') {
				curr_add++;
				j++;
			}

			curr_sum += ((curr_add) * (curr_add + 1))/2;
			j++;
		}

		ret = max(ret, curr_sum);

		cout << ret << endl;
		return;
	}

	// test out every permutation of # of letters in A choose k
	vector<vector<char>> permutes = gen_permutations(letters.size(), k);
	f0r(i, permutes.size()) {
		set<char> curr_permute;
		f0r(j, k) {
			curr_permute.insert(permutes[i][j]);
		}

		// now group each of these
		string temp_a = a;
		f0r(j, n) {
			if (curr_permute.count(temp_a[j]) > 0) {
				temp_a[j] = 'X';
			}
		}

		// sum em up now
		int j = 0;
		ll curr_sum = 0;
		while (j < n) {
			ll curr_add = 0;

			while (temp_a[j] == 'X') {
				curr_add++;
				j++;
			}

			curr_sum += ((curr_add) * (curr_add + 1))/2;
			j++;
		}

		ret = max(ret, curr_sum);
	}

	cout << ret << endl;
}
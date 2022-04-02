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

int main() {
	io;
	ll test_cases = 1;
	
	f0r(test_case, test_cases) {
		solve();
	}
}

void solve() {
	cin >> n;
    ll size = 2;
    f0r(i, n - 1) {
        size <<= 1;
    }

    vector<vector<ll> > vec(size, vector<ll> (size, -1));
    vector<vector<bool> > visited(size, vector<bool> (size, false));

    f0r(i, size) {
        f0r(j, size) {
            cin >> vec[i][j];
        }
    }

    bool ret = true;
    set<ll> my_set;
    f0r(i, size) {
        f0r(j, size) {
            ll curr = vec[i][j];

            DEBUG(my_set);
            // DEBUG(curr, my_set.find(curr) == my_set.end());
            // If this num has already been seen
            if (my_set.size() == 0 || visited[i][j] == false) {
                if(my_set.find(curr) == my_set.end()) {
                    my_set.insert(curr);
                } else {
                    ret = false;
                }
            }

            if (curr == 0) {
                visited[i][j] = true;
            } else if (visited[i][j] == false) {
                deque<pll > dq;
                dq.push_back(mp(i, j));
                ll counter = 1;
                vector<pll > pairs;

                while(!dq.empty()) {
                    pll current = dq.front();
                    visited[current.f][current.s] = true;

                    if (current.f - 1 >= 0 && visited[current.f - 1][current.s] == false && vec[current.f - 1][current.s] == curr) {
                        // Top
                        dq.push_front(mp(current.f - 1, current.s));
                        pairs.pb(mp(current.f - 1, current.s));
                        counter++;
                    } else if (current.s + 1 <= size - 1 && visited[current.f][current.s + 1] == false && vec[current.f][current.s + 1] == curr) {
                        // Right
                        dq.push_front(mp(current.f, current.s + 1));
                        pairs.pb(mp(current.f, current.s + 1));
                        counter++;
                    } else if (current.f + 1 <= size - 1 && visited[current.f + 1][current.s] == false && vec[current.f + 1][current.s] == curr) {
                        // Bottom
                        dq.push_front(mp(current.f + 1, current.s));
                        pairs.pb(mp(current.f + 1, current.s));
                        counter++;
                    } else if (current.s - 1 >= 0 && visited[current.f][current.s - 1] == false && vec[current.f][current.s - 1] == curr) {
                        // Left
                        dq.push_front(mp(current.f, current.s - 1));
                        pairs.pb(mp(current.f, current.s - 1));
                        counter++;
                    } else {
                        dq.pop_front();
                    }
                }
                pairs.pb(mp(i, j));

                DEBUG(pairs);
                if (counter != 3) {
                    DEBUG(i, j, counter);
                    ret = false;
                } else {
                    // check to make sure its L shape and not | or -
                    if (abs(pairs[0].f - pairs[1].f) != abs(pairs[0].s - pairs[2].s)) {
                        DEBUG(i, j, abs(pairs[0].f - pairs[1].f), abs(pairs[0].s - pairs[2].s));
                        ret = false;
                    }
                }
            }

        }
        if (!ret) break;
    }

    cout << ret << endl;
}
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

#define mp = make_pair
#define t third

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

ll n, q, Q, T, k, l, r, x, y, z, g;

ll solve(); 

int main() {
	io;
	ll test_cases = 1;
    cin >> test_cases;
	
	f0r(i, test_cases) {
		solve();
	}
}

template <typename T>
T expt(T p, unsigned q)
{
    T r(1);

    while (q != 0) {
        if (q % 2 == 1) {    // q is odd
            r *= p;
            q--;
        }
        p *= p;
        q /= 2;
    }

    return r;
}

ll solve() {
    cin >> x >> y;

    ll snd_largest_2 = 0;
    ll temp = y;
    while(temp > 1) {
        temp /= 2;
        snd_largest_2++;
    }
    snd_largest_2 = expt(2, snd_largest_2);
    DEBUG(snd_largest_2);

    ll temp_y = y;
    ll temp_x = x;
    while(snd_largest_2 > 1 && (temp_y - snd_largest_2 >= 0 || temp_x - snd_largest_2 < 0)) {
        temp_y %= snd_largest_2;
        temp_x %= snd_largest_2;
        snd_largest_2 /= 2;
        DEBUG(snd_largest_2, temp_y, temp_y - snd_largest_2, temp_x, temp_x - snd_largest_2);
    }
    snd_largest_2 *= 2;
    DEBUG(snd_largest_2);

    ll new_x = x % snd_largest_2;
    ll new_y = y % snd_largest_2;
    DEBUG(x, new_x, y, new_y);

    if(new_x == 0) {
        cout << 1 << endl;
        return 0;
    }

    ll first_up = 0;
    ll second_up;
    second_up = abs(new_x - new_y) + 1;
    DEBUG(y, snd_largest_2 * 2);
    DEBUG((y % (snd_largest_2 * 2)) - snd_largest_2);
    if(((y % (snd_largest_2 * 2)) - snd_largest_2) >= 0) {
        ll first_up = abs(snd_largest_2 - new_x + new_y) + 1;
        if (snd_largest_2 * 2 >= y) {
            first_up--;
        }
        DEBUG(first_up, second_up);
        cout << min(first_up, second_up) << endl;
    } else {
        cout << second_up << endl;
    }

    return -1;
}
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

vector<ll> pref;

ll bestForLen(int len) {
	ll ret = LLONG_MIN;
	f1r(i, len, n + 1) {
		ret = max(ret, pref[i] - pref[i - len]);
	}

	return ret;
}

/* Scuffed Edits were made to make sure that the length is at least > k since otherwise it overlaps with bestForLen when accounting for smaller subsets and don't add full 2kx */

// A utility function to find maximum of two integers
ll max(ll a, ll b) { return (a > b) ? a : b; }
  
// A utility function to find maximum of three integers
ll max(ll a, ll b, ll c) { return max(max(a, b), c); }

// Find the maximum possible sum in arr[] such that arr[m]
// is part of it
ll maxCrossingSum(ll arr[], int l, int m, int h)
{
	/* Scuffed Edit to make sure that the length is at least > k since otherwise it overlaps with bestForLen when accounting for smaller subsets and don't add full 2kx */
	if (h - l <= k) {
		return LLONG_MIN;
	}
    // Include elements on left of mid.
    ll sum = 0;
    ll left_sum = LLONG_MIN;
    for (int i = m; i >= l; i--) {
        sum = sum + arr[i];
        if (sum > left_sum)
            left_sum = sum;
    }
  
    // Include elements on right of mid
    sum = 0;
    ll right_sum = LLONG_MIN;
    for (int i = m; i <= h; i++) {
        sum = sum + arr[i];
        if (sum > right_sum)
            right_sum = sum;
    }
  
    // Return sum of elements on left and right of mid
    // returning only left_sum + right_sum will fail for
    // [-2, 1]
    return max(left_sum + right_sum - arr[m], left_sum, right_sum);
}
  
// Returns sum of maximum sum subarray in aa[l..h]
ll maxSubArraySum(ll arr[], int l, int h)
{
	if (h - l <= k) {
		return LLONG_MIN;
	}

      //Invalid Range: low is greater than high
      if (l > h)
          return LLONG_MIN;
    // Base Case: Only one element
    if (l == h)
        return arr[l];
  
    // Find middle point
    int m = (l + h) / 2;
  
    /* Return maximum of following three possible cases
            a) Maximum subarray sum in left half
            b) Maximum subarray sum in right half
            c) Maximum subarray sum such that the subarray
       crosses the midpoint */
    return max(maxSubArraySum(arr, l, m - 1),
               maxSubArraySum(arr, m + 1, h),
               maxCrossingSum(arr, l, m, h));
}

void solve() {
	cin >> n >> k >> x;
	vector<int> inp(n);

	f0r(i, n) {
		cin >> inp[i];
	}

	f0r(i, n) {
		inp[i] -= x;
	}

	pref = vector<ll>(n + 1, 0);
	f1r(i, 1, n) {
		pref[i] = pref[i - 1] + inp[i - 1];
	}

	ll best = 0;
	f1r(i, 1, k + 1) {
		best = max(best, bestForLen(i) + 2 * i * x);
		DEBUG(i, best);
	}

	ll arr[n];
	f0r(i, n) {
		arr[i] = inp[i];
	}

	ll max_sum = maxSubArraySum(arr, 0, n - 1);
	max_sum += k * 2 * x;

	DEBUG(best, max_sum);
	cout << max(max_sum, 0, best) << endl;
}

/*
this is easy
u HAVE to do it once
ur forced to do the operation
so now i just need to get
max subarray of length 0, 1, all the way up to 20
call that length like Z
then i add Z2x to that or something 
and then just general greatest sum and add 20x * 2 ig
this is trivially done with prefix sums
cuz then u just do a O(n) sweep thru
20 times cuz ur given max k can be at most 20
like if u want subarray of length 15. ur at index 5, look at index 20. prefix sum, and then move onto index 6 -> 21 or some shit
trivial

and then that gfg https://www.geeksforgeeks.org/maximum-subarray-sum-using-divide-and-conquer-algorithm/ 

and then 0 
and take the max of all those answers
*/
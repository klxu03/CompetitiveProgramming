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
    freopen((filename + ".txt").c_str(), "r", stdin);
    freopen((filename + "_output.txt").c_str(), "w", stdout);
}

ll q, Q, T, k, l, r, x, y, z, g;
ll n, m;

void solve(); 

/* 
This is wrong, I need to check not if it's split in half
but if it is ABCABCABC it should be yes if already ordered
but in half it's not, but its fine since you can move ABC to the end

1
9 1
1 2 3 1 2 3 1 2 3
1 2 3 1 2 3 1 2 3

My code outputs "NO", it should be "YES"
*/


// Problem: https://www.facebook.com/codingcompetitions/hacker-cup/2022/round-1/problems/A2
int main() {
	io;
    // usaco("consecutive_cuts_chapter_2_input");
	ll test_cases = 1;
    cin >> test_cases;
	
	f0r(test_case, test_cases) {
        cout << "Case #" << test_case + 1 << ": ";
		solve();
	}
}

vector<int> compute_lps(vector<ll> pat) {
    int n = pat.size();
    vector<int> lps(n);
    lps[0] = 0;
    for (int i = 1; i < n; i++) {
        lps[i] = 0;
        int j = lps[i - 1]; /* trying length j + 1 */
        while (j > 0 && pat[j] != pat[i]) {
            j = lps[j - 1];
        }
        if (pat[j] == pat[i]) {
            lps[i] = j + 1;
        }
    }
    return lps;
}

vector<int> find_matches(vector<ll> text, vector<ll> pat) {
    int n = pat.size(), m = text.size();
    vector<ll> v = pat;
    v.push_back(-1);
    v.insert(v.end(), text.begin(), text.end());
    vector<int> lps = compute_lps(v), ans;
    for (int i = n + 1; i <= n + m; i++) { /* n + 1 is where the text starts */
        if (lps[i] == n) {
            ans.push_back(i - 2 * n); /* i - (n - 1) - (n + 1) */
        }
    }
    return ans;
}

void solve() {
	cin >> n >> k;
    vector<ll> A(n);
    vector<ll> B(n);

    bool already_ordered = true; // A == B
    bool same_order = false; // A has the same order as B

    f0r(i, n) {
        cin >> A[i];
    }

    f0r(i, n) {
        cin >> B[i];
        if (already_ordered && A[i] != B[i]) {
            already_ordered = false;
        }
    }

    // Figure out if same_order with some cool KMF and doubling B stuff to get exact index
    
    // Double B into a new vector called B2
    vector<ll> B2 = B;
    B2.insert(B2.end(), B.begin(), B.end());

    vector<int> ans = find_matches(B2, A);
    same_order = ans.size() >= 1; // ans.size() could be 2 if already_ordered, or more if replicas etc.

    // DEBUG(already_ordered, same_order, ans);

    if (same_order) {
        if (n == 2) {
            if (A[0] == A[1]) {
                // AA case, so YES regardless of whether or not k is even or odd
                cout << "YES" << endl;
            } else if (already_ordered) {
                // Not AA or the exact same, so AB
                if (k % 2 == 0) {
                    cout << "YES" << endl;
                } else {
                    // n = 2, already ordered, and k is odd
                    cout << "NO" << endl;
                }
            } else {
                // Not AA or the exact same, so BA and not ordered
                if (k % 2 == 1) {
                    cout << "YES" << endl;
                } else {
                    // n = 2, not ordered, and k is even
                    cout << "NO" << endl;
                }

            }
        } else {
            // n >= 3
            if (already_ordered) {
                if (k == 1) {
                    // Check if I can split like AAA (odd number) or ABCABC (even, same splitting mirror), then K = 1 still being right is fine. Otherwise NO

                    // Check if each card is the same
                    bool each_card_is_same = true;
                    f0r(i, A.size()) {
                        if (A[i] != A[0]) {
                            each_card_is_same = false;
                            break;
                        }
                    }

                    bool halfway_exact_same = true;
                    if (A.size() % 2 == 1) {
                        // A must be an even size
                        halfway_exact_same = false;
                    } else {
                        vector<ll> first_half;
                        f0r(i, A.size()/2) {
                            first_half.pb(A[i]);
                        }

                        f0r(i, A.size()/2) {
                            if (first_half[i] != A[A.size()/2 + i]) {
                                halfway_exact_same = false;
                                break;
                            }
                        }
                    }

                    // DEBUG(each_card_is_same, halfway_exact_same);

                    /* 
                    This is wrong, I need to check not if it's split in half
                    but if it is ABCABCABC it should be yes if already ordered
                    but in half it's not, but its fine since you can move ABC to the end

                    1
                    9 1
                    1 2 3 1 2 3 1 2 3
                    1 2 3 1 2 3 1 2 3

                    My code outputs "NO", it should be "YES"
                    */

                    if (each_card_is_same || halfway_exact_same) {
                        cout << "YES" << endl;
                    } else {
                        cout << "NO" << endl;
                    }
                } else {
                    cout << "YES" << endl;
                }
            } else {
                // Not already ordered
                if (k == 0) {
                    // Not ordered already and k = 0
                    cout << "NO" << endl;
                } else {
                    cout << "YES" << endl;
                }
            }
        }
    } else {
        cout << "NO" << endl;
    }
}
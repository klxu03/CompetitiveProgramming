// https://leetcode.com/contest/weekly-contest-314/problems/using-a-robot-to-print-the-lexicographically-smallest-string/

#include <bits/stdc++.h>

using namespace std;

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = c - 1; a >= b; a--)
#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define max3(a, b, c) max(a, max(b, c))
#define pb push_back
#define f first
#define s second
#define mp(a, b) make_pair(a, b)

using ll = long long;

/* Print a vector */
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {cout << "[";for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];}return cout << "]";}

/* For Debugging Purposes */
#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#else
#define DEBUG(...) 6
#endif

template<typename T, typename S> ostream& operator << (ostream &os, const pair<T, S> &p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename C, typename T = decay<decltype(*begin(declval<C>()))>, typename enable_if<!is_same<C, string>::value>::type* = nullptr>
ostream& operator << (ostream &os, const C &c) {bool f = true; os << "["; for (const auto &x : c) {if (!f) os << ", "; f = false; os << x;} return os << "]";}
template<typename T> void debug(string s, T x) {cerr << s << " = " << x << "\n";}
template <typename T, typename... Args> void debug(string s, T x, Args... args) {for (int i=0, b=0; i<(int)s.size(); i++) if (s[i] == '(' || s[i] == '{') b++;
else if (s[i] == ')' || s[i] == '}') b--; else if (s[i] == ',' && b == 0) {cerr << s.substr(0, i) << " = " << x << " | "; debug(s.substr(s.find_first_not_of(' ', i + 1)), args...); break;}}

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

class Solution {
public:
    deque<char> t;
    string inp;
    string res;

    vector<int> last; // last[1] means last occurance of b
    vector<char> next_smallest; // next_smallest[2] == 'd' means the next smallest char after 3rd element is 'd'

    // n is starting index inclusive
    void recurse(int n, char c) {
        int last_occur = last[c - 'a'];
        DEBUG(n, c, last_occur);
        DEBUG(t);
        while (!t.empty() && t.back() <= c) {
            res.pb(t.back());
            t.pop_back();
        }
        DEBUG(t);

        f1r(i, n, last_occur + 1) {
            if (inp[i] == c) {
                res.pb(inp[i]);
            } else {
                t.pb(inp[i]);
            }
        }
        DEBUG(t);
        DEBUG(res);

        // Ending recursion return the call stack
        if (last_occur + 1 >= inp.size()) {
            while (!t.empty()) {
                res.pb(t.back());
                t.pop_back();
            }

            return;
        }

        recurse(last_occur + 1, next_smallest[last_occur + 1]);
    }

    string robotWithString(string s) {
        inp = s;
        res = "";
        last = vector<int>(27); // # of letters

        f0r(i, s.size()) {
            last[s[i] - 'a'] = i;
        }
        
        next_smallest = vector<char>(s.size());
        char running_min = 'z';
        r0f(i, s.size()) {
            running_min = min(running_min, s[i]);
            DEBUG(i, running_min);
            next_smallest[i] = running_min;
        }

        DEBUG(last);
        DEBUG(next_smallest);

        DEBUG(res);
        recurse(0, next_smallest[0]);
        DEBUG(res);

        return res;
    }
};
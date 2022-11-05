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

// [1, 2, 8, 64, 1024, 32768, 2097152, 268435456, 719476260, 371842544, 766762396, 329376018, 124160285, 121047601, 243880903, 489373567, 585862415, 157921350, 134084614, 953612746, 431750151, 686331837, 349105660, 511821710, 322050759, 217770278, 867243987, 742004924, 733922348, 549790477]

class Solution {
public:
    int minimizeArrayValue(vector<int>& nums) {
        ll lo = -1, hi = -1;
        ll sum = -1;

        ll actual_max = nums[0];
        f1r(i, 1, nums.size()) {
            if (nums[i] > actual_max) {
                actual_max = nums[i];
            }

            if (nums[i] - nums[i - 1] > 0 && nums[i] + nums[i - 1] > sum) {
                lo = i - 1;
                hi = i;
                sum = nums[i] + nums[i - 1];
            }
        }

        DEBUG(nums[lo], nums[hi], sum);

        if (sum == -1) {
            return actual_max;
        }

        if (sum % 2 == 1) {
            return sum/2 + 1;
        } else {
            return sum/2;
        }
    }
};

int main() {
    Solution s;
    vector<int> nums = {3, 7, 1, 6};

    cout << s.minimizeArrayValue(nums);
}
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

#define mp = make_pair
#define t third

/* For Debugging Purposes */
#ifdef LOCALasdf
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

/* Sorts pairs based off of first index, otherwise gives the second one in opposite direction (first it gives highest then lowest, for second it goes from lowest to highest)
https://repl.it/join/agispdrw-kevinxu6
*/
bool sortWithLocation(pair<int, int>& a, pair<int, int>& b) {
    //This is checking the indices (location in array), or the number on the right only if the first value, or the value of the thing is the same
    if (a.first == b.first) {
        return a.second < b.second;
    }
    //This is checking the first value, or the thing on the left and descendingily sorting right now
    return a.first > b.first;
}

/* Print a vector */
template<typename A> ostream& operator<<(ostream& cout, vector<A> const& v) {
    cout << "["; for (int i = 0; i < v.size(); i++) { if (i) cout << ", "; cout << v[i]; } return cout << "]";
}

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

/**
Checks to see if a trait exists in the map, if it exists returns true, if it doesn't exist in the map returns false
*/
bool existInMap(map<string, int> map, string trait) {
    if (map.find(trait) == map.end()) {
        return false;
    }
    return true;
}

/**
Instantiate a global variable set s, and then check of "input" is inside set s. If it is inside set s, return true otherwise return false
*/
set <string> sets;
bool existInSet(string input) {
    if (sets.find(input) == sets.end()) {
        return false;
    }
    return true;
}

/**
Checks a 2D array to see if every single value inside the 2D array is true. If every value is true, this helper method will return true, otherwise it will return false.
*/
bool allTrue(vector<vector<bool> > vec) {
    bool output = true;
    ll i = 0, j = 0;

    while (i < vec.size() && output) {
        while (j < vec[i].size() && output) {
            // // cout << "vec[i][j] is " << vec[i][j] << endl;
            output &= vec[i][j];
            j++;
        }

        i++;
        j = 0;
    }

    return output;
}

void readHashSet(unordered_set<ll> set) {
    cout << "Hashset Contents: ";
    for (auto i = set.begin(); i != set.end(); ++i) {
        cout << (*i) << " ";
    }
    cout << endl;
}

// pair<type1, type2> p;
// p.f = 0;
// cout << p.f << p.s << '\n'

/*
How to use Array Sort in C++
  int cows[n];
  sort(cows, cows + n);

  Start location is just the array (since it's a pointer), and end position is just the array + n, or length of array

*/

struct triplet {
    ll first, second; string third;

    void make_triplet(ll firstValue, ll secondValue, string thirdValue) {
        first = firstValue;
        second = secondValue;
        third = thirdValue;
    }
};

/*
Returns the index of the minimum value in the vector
*/
ll findIndexOfMin(vector<ll> param) {
    ll min = LLONG_MAX;
    ll index = 0;
    f0r(i, param.size()) {
        if (param[i] < min) {
            min = param[i];
            index = i;
        }
    }
    return index;
}

/*
Returns the index of the max value in the vector
*/
ll findIndexOfMax(vector<ll> param) {
    ll max = LLONG_MIN;
    ll index = 0;
    f0r(i, param.size()) {
        if (param[i] > max) {
            max = param[i];
            index = i;
        }
    }
    return index;
}

ll n, q, Q, T, t, k, l, r, z, g;

int main() {
    io;

    cin >> t;
    f0r(i, t) {
        ll a, b;
        cin >> a >> b;
        DEBUG(a, b);
        ll counter = 0;

        if (b == 1) {
            b++;
            counter++;
        }

        ll times;
        if (a < b) {
            counter++;
            goto done;
        } else if (a == b) {
            counter = 2;
            DEBUG(counter);
            goto done;
        }

        double x, y;
        while(true) {
            x = (log(a)/log(b));
            y = (log(a)/log(b + 1));

            DEBUG(x, y);
            if (y + 1 >= x) {
                goto while_done;
            } else {
                b++;
                counter++;
            }
            DEBUG(counter, b);
        }
        while_done:

        DEBUG(counter, a, b);

        // x = (ll)(log(a)/log(b));
        // if (x > b) {
        //     counter += x - b;
        //     DEBUG(counter, x - b, x, b);
        //     b = x;
        // }

        times = (ll) (log(a)/log(b));
        counter += times;
        // DEBUG((ll) (log(a)/log(b)), ceil(log(a)/log(b)));

        // while(a > b) {
        //     a /= b;
        //     // DEBUG(a);
        //     counter++;
        // }
        
        DEBUG(times, a, b, (ll) floor(a/pow(b, times)));
        if ((ll) floor(a/pow(b, times)) == b) {
            counter += 2;
        } else {
            counter++;
        }

        done:

        cout << counter << endl;
    }
}
//http://www.usaco.org/index.php?page=viewproblem2&cpid=787

#include <bits/stdc++.h>

using namespace std;

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)

#define max3(a, b, c) max(a, max(b, c))
#define pb push_back
#define f first
#define s second
#define mp(a, b) make_pair(a, b)

using ll = long long;

/* Print a vector */
template <typename A>
ostream &operator<<(ostream &cout, vector<A> const &v)
{
    cout << "[";
    for (int i = 0; i < v.size(); i++)
    {
        if (i)
            cout << ", ";
        cout << v[i];
    }
    return cout << "]";
}

/* For Debugging Purposes */
#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__);
#else
#define DEBUG(...) 6;
#endif

template<typename T, typename S> ostream& operator << (ostream &os, const pair<T, S> &p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename C, typename T = decay<decltype(*begin(declval<C>()))>, typename enable_if<!is_same<C, string>::value>::type* = nullptr>
ostream& operator << (ostream &os, const C &c) {bool f = true; os << "["; for (const auto &x : c) {if (!f) os << ", "; f = false; os << x;} return os << "]";}
template<typename T> void debug(string s, T x) {cerr << s << " = " << x << "\n";}
template<typename T, typename... Args> void debug(string s, T x, Args... args) {cerr << s.substr(0, s.find(',')) << " = " << x << " | "; debug(s.substr(s.find(',') + 2), args...);}

#define io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
void usaco(string filename) {
    io;
    freopen((filename + ".in").c_str(), "r", stdin);
    freopen((filename + ".out").c_str(), "w", stdout);
}

ll n, m, r;

ll money(ll gallons, vector<pair<ll, ll> > &gallon, ll &gallon_counter) {
    ll output = 0;

    while (gallons > 0 && gallon_counter <= gallon.size()) {
        if (gallon[gallon_counter].f > gallons) { // If the farmer is willing to buy more milk than how much the cow can produce
            gallon[gallon_counter].f -= gallons;
            output += gallons * gallon[gallon_counter].s;
            gallons = 0;
        } else {
            gallons -= gallon[gallon_counter].f;
            output += gallon[gallon_counter].s * gallon[gallon_counter].f;
            gallon[gallon_counter].f = 0;
            gallon_counter++;
        }
    }

    return output;
}

int main() {
    usaco("rental");
    cin >> n >> m >> r;

    vector<ll> cows(n);             // A vector of the amount of gallons a cow can produce
    vector<pair<ll, ll> > gallon(m); // A vector of pairs of pair.f # of gallons willing to buy and pair.s $ per gallon
    vector<ll> rent(r);             // Amount of money to rent a cow per day

    f0r(i, n) {
        cin >> cows[i];
    }
    
    sort(cows.begin(), cows.end(), [](ll &a, ll &b) { return a > b; });

    f0r(i, m) {
        ll a, b;
        cin >> a >> b;
        gallon[i] = mp(a, b);
    }

    sort(gallon.begin(), gallon.end(), [](pair<ll, ll> &a, pair<ll, ll> &b) { return a.s > b.s; });

    f0r(i, r) {
        cin >> rent[i];
    }

    sort(rent.begin(), rent.end(), [](ll &a, ll &b) { return a > b; });
    DEBUG(cows, gallon, rent);

    ll gallon_counter = 0;
    ll rent_counter = 0;
    ll output = 0;
    ll currOutput = 0;
    bool do_the_function = true;

    ll i = 0, n_2 = n;
    while (i < n_2) {
        DEBUG(currOutput, i, n_2, gallon, rent_counter, output, do_the_function);

        if (do_the_function) { // Go through the money helper function again
            currOutput = money(cows[i], gallon, gallon_counter);
            DEBUG(currOutput, rent[rent_counter]);

            if (currOutput > rent[rent_counter]) { // If you make more money selling the cow's milk
                output += currOutput;
                currOutput = 0;
                do_the_function = true;
                i++;
            } else {
                n_2--;
                output += rent[rent_counter];
                rent_counter++;
                do_the_function = false;
            }            
        } else {
            DEBUG(currOutput, rent[rent_counter]);

            if (currOutput > rent[rent_counter]) { // If you make more money selling the cow's milk
                output += currOutput;
                currOutput = 0;
                do_the_function = true;
                i++;
            } else {
                n_2--;
                output += rent[rent_counter];
                rent_counter++;
                do_the_function = false;
            }
        }

    }

    cout << output << endl;
}
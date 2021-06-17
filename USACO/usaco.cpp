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
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {
    cout << "["; 
    for(int i = 0; i < v.size(); i++) {
    if (i) cout << ", "; cout << v[i];
    } 
    return cout << "]";
}

int main() {
    ll n;
    cin >> n;

    vector<char> dir(n); 
    vector<ll> x(n);
    vector<ll> y(n);

    f0r(i, n) {
        cin >> dir[i] >> x[i] >> y[i];
    }

    vector<ll> ans(n);

    f0r(i, n) {
        f0r(j, n) {
            if (i == j && i != n - 1) j++;
            if (i == j && i == n - 1) break;
            
            if (dir[i] == 'N')
                if (y[j] >= y[i]) {
                    if (dir[j] == 'E' && x[j] <= x[i]) {
                        if (x[i] - x[j] > y[j] - y[i]) {
                            ans[i]++;
                        } else if (x[i] - x[j] == y[j] - y[i]) {
                            continue;
                        } else {
                            break;
                        }
                    } 
                    if (dir[j] == 'W' && x[j] >= x[i]) {
                        if (x[j] - x[i] > y[j] - y[i]) {
                            ans[i]++;
                        } else if (x[j] - x[i] == y[j] - y[i]) {
                            continue;
                        } else {
                            break;
                        }
                    }
                }
            
            if (dir[i] == 'S')
                if (y[j] <= y[i]) {
                    ll pro = x[i] - x[j];
                    ll con = y[i] - y[j];
                    if (dir[j] == 'E' && x[j] <= x[i]) {
                        if (pro > con) {
                            ans[i]++;
                        } else if (pro == con) {
                            continue;
                        } else {
                            break;
                        }
                    } 
                    if (dir[j] == 'W' && x[j] >= x[i]) {
                        if (x[j] - x[i] > y[j] - y[i]) {
                            ans[i]++;
                        } else if (x[j] - x[i] == y[j] - y[i]) {
                            continue;
                        } else {
                            break;
                        }
                    }
                }

            if (dir[i] == 'W')
                if (x[j] <= x[i]) {
                    if (dir[j] == 'N')
                        if (y[j] <= y[i]) ans[i]++;
                    if (dir[j] == 'S')
                        if (y[j] >= y[i]) ans[i]++;
                }
        }
    }

    vector<ll> new_ans(n);
    f0r(i, n) {
        new_ans[i] = ans[i];
    }

    f0r(i, n) {
        f0r(j, n) {
            if (i == j && i != n - 1) j++;
            if (i == j && i == n - 1) break;

            if (dir[i] == 'N')
                if (y[j] >= y[i]) {
                    if (dir[j] == 'E') 
                        if (x[j] <= x[i]) new_ans[i] += ans[j];
                    if (dir[j] == 'W')
                        if (x[j] >= x[i]) new_ans[i] += ans[j];
                }
            
            if (dir[i] == 'S')
                if (y[j] <= y[i]) {
                    if (dir[j] == 'E') 
                        if (x[j] <= x[i]) new_ans[i] += ans[j];
                    if (dir[j] == 'W')
                        if (x[j] >= x[i]) new_ans[i] += ans[j];
                }
            
            if (dir[i] == 'E')
                if (x[j] >= x[i]) {
                    if (dir[j] == 'N')
                        if (y[j] <= y[i]) new_ans[i] += ans[j];
                    if (dir[j] == 'S')
                        if (y[j] >= y[i]) new_ans[i] += ans[j];
                }

            if (dir[i] == 'W')
                if (x[j] <= x[i]) {
                    if (dir[j] == 'N')
                        if (y[j] <= y[i]) new_ans[i] += ans[j];
                    if (dir[j] == 'S')
                        if (y[j] >= y[i]) new_ans[i] += ans[j];
                }
        }
    }

    f0r(i, n) {
        cout << ans[i] << endl;
    }

}
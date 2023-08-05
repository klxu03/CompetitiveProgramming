#include <bits/stdc++.h>

using namespace std;
using ll = long long;

//Safe lowerbound for 1 second is 10^8 operations

#define f0r(a, b) for (long long a = 0; a < b; a++)
#define f1r(a, b, c) for (long long a = b; a < c; a++)
#define r0f(a, b) for (long long a = b - 1; a >= 0; a--)
#define r1f(a, b, c) for (long long a = b; a >= c; a--)
#define pb push_back
#define f first
#define s second

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

namespace algebra {

    template <std::uint32_t P>
    struct ModInt32 {
    public:
        using i32 = std::int32_t;
        using u32 = std::uint32_t;
        using i64 = std::int64_t;
        using u64 = std::uint64_t;
        using m32 = ModInt32;
        using internal_value_type = u32;

        u32 v;
        static constexpr u32 get_r() {
            u32 iv = P;
            for (u32 i = 0; i != 4; ++i) iv *= 2U - P * iv;
            return -iv;
        }
        static constexpr u32 r = get_r(), r2 = -u64(P) % P;
        static_assert((P & 1) == 1);
        static_assert(-r * P == 1);
        static_assert(P < (1 << 30));
        static constexpr u32 pow_mod(u32 x, u64 y) {
            u32 res = 1;
            for (; y != 0; y >>= 1, x = u64(x) * x % P)
                if (y & 1) res = u64(res) * x % P;
            return res;
        }
        static constexpr u32 reduce(u64 x) {
            return (x + u64(u32(x) * r) * P) >> 32;
        }
        static constexpr u32 norm(u32 x) { return x - (P & -(x >= P)); }

    public:
        static constexpr u32 get_pr() {
            u32 tmp[32] = {}, cnt = 0;
            const u64 phi = P - 1;
            u64 m = phi;
            for (u64 i = 2; i * i <= m; ++i)
                if (m % i == 0) {
                    tmp[cnt++] = u32(i);
                    while (m % i == 0) m /= i;
                }
            if (m != 1) tmp[cnt++] = u32(m);
            for (u64 res = 2; res != P; ++res) {
                bool flag = true;
                for (u32 i = 0; i != cnt && flag; ++i)
                    flag &= pow_mod(res, phi / tmp[i]) != 1;
                if (flag) return u32(res);
            }
            return 0;
        }

        constexpr ModInt32() = default;
        ~ModInt32() = default;
        constexpr ModInt32(const m32& rhs) = default;
        constexpr m32& operator=(const m32& rhs) = default;
        constexpr ModInt32(m32&& rhs) = default;
        constexpr m32& operator=(m32&& rhs) = default;

        constexpr ModInt32(u32 _v) : v(reduce(u64(_v) * r2)) {}
        constexpr ModInt32(i32 _v)
                : v(reduce(u64(_v % i64(P) + i64(P)) * r2)) {}
        constexpr ModInt32(u64 _v) : v(reduce((_v % P) * r2)) {}
        constexpr ModInt32(i64 _v)
                : v(reduce(u64(_v % i64(P) + i64(P)) * r2)) {}
        constexpr u32 get() const { return norm(reduce(v)); }
        explicit constexpr operator u32() const { return get(); }
        explicit constexpr operator i32() const { return i32(get()); }
        constexpr m32 operator-() const {
            m32 res;
            return res.v = (P << 1 & -(v != 0)) - v, res;
        }
        constexpr m32 inv() const { return pow(-1); }
        constexpr m32& operator+=(const m32& rhs) {
            return v += rhs.v - (P << 1), v += P << 1 & -(v >> 31), *this;
        }
        constexpr m32& operator-=(const m32& rhs) {
            return v -= rhs.v, v += P << 1 & -(v >> 31), *this;
        }
        constexpr m32& operator*=(const m32& rhs) {
            return v = reduce(u64(v) * rhs.v), *this;
        }
        constexpr m32& operator/=(const m32& rhs) {
            return this->operator*=(rhs.inv());
        }
        friend m32 operator+(const m32& lhs, const m32& rhs) {
            return m32(lhs) += rhs;
        }
        friend m32 operator-(const m32& lhs, const m32& rhs) {
            return m32(lhs) -= rhs;
        }
        friend m32 operator*(const m32& lhs, const m32& rhs) {
            return m32(lhs) *= rhs;
        }
        friend m32 operator/(const m32& lhs, const m32& rhs) {
            return m32(lhs) /= rhs;
        }
        friend bool operator==(const m32& lhs, const m32& rhs) {
            return norm(lhs.v) == norm(rhs.v);
        }
        friend bool operator!=(const m32& lhs, const m32& rhs) {
            return norm(lhs.v) != norm(rhs.v);
        }
        template <class T>
        friend T& operator>>(T& is, m32& rhs) {
            return is >> rhs.v, rhs.v = reduce(u64(rhs.v) * r2), is;
        }
        template <class T>
        friend T& operator<<(T& os, const m32& rhs) {
            return os << rhs.get();
        }
        constexpr m32 pow(i64 y) const {
            i64 rem = y % (P - 1);
            if (y > 0 && rem == 0)
                y = P - 1;
            else
                y = rem;
            if (y < 0) y += P - 1;
            m32 res(1), x(*this);
            for (; y != 0; y >>= 1, x *= x)
                if (y & 1) res *= x;
            return res;
        }
    };
    template <std::uint32_t P>
    ModInt32<P> sqrt(const ModInt32<P>& x) {
        using value_type = ModInt32<P>;
        static constexpr value_type negative_one(P - 1), ZERO(0);
        if (x == ZERO || x.pow((P - 1) >> 1) == negative_one) return ZERO;
        if ((P & 3) == 3) return x.pow((P + 1) >> 2);
        static value_type w2, ax;
        ax = x;
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<std::uint32_t> dis(1, P - 1);
        const value_type four(value_type(4) * x);
        static value_type t;
        do t = value_type(dis(gen)), w2 = t * t - four;
        while (w2.pow((P - 1) >> 1) != negative_one);
        struct Field_P2 {  // (A + Bx)(C+Dx)=(AC-BDa)+(AD+BC+BDt)x
        public:
            value_type a, b;
            Field_P2(const value_type& a, const value_type& b) : a(a), b(b) {}
            ~Field_P2() = default;
            Field_P2& operator*=(const Field_P2& rhs) {
                value_type tmp1(b * rhs.b), tmp2(a * rhs.a - tmp1 * ax),
                        tmp3(a * rhs.b + b * rhs.a + tmp1 * t);
                return a = tmp2, b = tmp3, *this;
            }
            Field_P2 pow(std::uint64_t y) const {
                Field_P2 res(value_type(1), ZERO), x(*this);
                for (; y != 0; y >>= 1, x *= x)
                    if (y & 1) res *= x;
                return res;
            }
        } res(ZERO, value_type(1));
        return res.pow((P + 1) >> 1).a;
    }
    std::uint64_t get_len(std::uint64_t n) {  // if n=0, boom
        return --n, n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8,
                    n |= n >> 16, n |= n >> 32, ++n;
    }
    template <std::uint32_t P>
    struct NTT {
    public:
        using i32 = std::int32_t;
        using u32 = std::uint32_t;
        using i64 = std::int64_t;
        using u64 = std::uint64_t;
        using value_type = ModInt32<P>;

    private:
        static inline value_type ROOT[1 << 20], IROOT[1 << 20];

    public:
        NTT() = delete;
        static void idft(i32 n, value_type x[]) {
            for (i32 i = 2; i < n; i <<= 1) {
                for (i32 j = 0, l = i >> 1; j != l; ++j) {
                    value_type u = x[j], v = x[j + l];
                    x[j] = u + v, x[j + l] = u - v;
                }
                for (i32 j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {
                    value_type root = IROOT[m];
                    for (i32 k = 0; k != l; ++k) {
                        value_type u = x[j + k], v = x[j + k + l];
                        x[j + k] = u + v, x[j + k + l] = (u - v) * root;
                    }
                }
            }
            value_type iv(P - (P - 1) / n);
            for (i32 j = 0, l = n >> 1; j != l; ++j) {
                value_type u = x[j] * iv, v = x[j + l] * iv;
                x[j] = u + v, x[j + l] = u - v;
            }
        }
        static void dft(i32 n, value_type x[]) {
            static i32 lim = 0;
            static constexpr u32 pr = value_type::get_pr();
            static_assert(pr != 0);
            static constexpr value_type G(pr);
            if (lim == 0) {
                ROOT[1 << 19] = G.pow((P - 1) >> 21),
                        IROOT[1 << 19] = G.pow(P - 1 - i32((P - 1) >> 21));
                for (i32 i = 18; i != -1; --i)
                    ROOT[1 << i] = ROOT[1 << (i + 1)] * ROOT[1 << (i + 1)],
                            IROOT[1 << i] =
                                    IROOT[1 << (i + 1)] * IROOT[1 << (i + 1)];
                lim = 1;
            }
            while ((lim << 1) < n) {
                for (i32 i = lim + 1, e = lim << 1; i < e; ++i)
                    ROOT[i] = ROOT[i - lim] * ROOT[lim],
                            IROOT[i] = IROOT[i - lim] * IROOT[lim];
                lim <<= 1;
            }
            for (i32 j = 0, l = n >> 1; j != l; ++j) {
                value_type u = x[j], v = x[j + l];
                x[j] = u + v, x[j + l] = u - v;
            }
            for (i32 i = n >> 1; i >= 2; i >>= 1) {
                for (i32 j = 0, l = i >> 1; j != l; ++j) {
                    value_type u = x[j], v = x[j + l];
                    x[j] = u + v, x[j + l] = u - v;
                }
                for (i32 j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {
                    value_type root = ROOT[m];
                    for (i32 k = 0; k != l; ++k) {
                        value_type u = x[j + k], v = x[j + k + l] * root;
                        x[j + k] = u + v, x[j + k + l] = u - v;
                    }
                }
            }
        }
    };
    template <std::uint32_t P>
    void dft(std::uint32_t n, ModInt32<P> x[]) {
        NTT<P>::dft(n, x);
    }
    template <std::uint32_t P>
    void idft(std::uint32_t n, ModInt32<P> x[]) {
        NTT<P>::idft(n, x);
    }
    template <std::uint32_t P>
    std::int32_t deg(const std::basic_string<ModInt32<P>>& x) {
        // return -1 if x is 0
        std::int32_t n = std::int32_t(x.size()) - 1;
        static constexpr ModInt32<P> ZERO(0);
        while (n >= 0 && x[n] == ZERO) --n;
        return n;
    }
    template <std::uint32_t P>
    std::basic_string<ModInt32<P>>& norm(std::basic_string<ModInt32<P>>& x) {
        return x.resize(std::max(deg(x) + 1, 1)), x;
    }
    template <std::uint32_t P>
    std::basic_string<ModInt32<P>> norm(std::basic_string<ModInt32<P>>&& x) {
        return x.resize(std::max(deg(x) + 1, 1)), x;
    }
    template <std::uint32_t P>
    std::basic_string<ModInt32<P>> add(
            const std::basic_string<ModInt32<P>>& x,
            const std::basic_string<ModInt32<P>>& y) {
        using i32 = std::int32_t;
        using value_type = ModInt32<P>;
        std::basic_string<value_type> res(std::max(x.size(), y.size()), {});
        for (i32 i = 0, e = std::min(x.size(), y.size()); i != e; ++i)
            res[i] = x[i] + y[i];
        if (x.size() < y.size())
            std::copy(y.begin() + x.size(), y.end(), res.begin() + x.size());
        else
            std::copy(x.begin() + y.size(), x.end(), res.begin() + y.size());
        return norm(res);
    }
    template <std::uint32_t P>
    std::basic_string<ModInt32<P>> sub(
            const std::basic_string<ModInt32<P>>& x,
            const std::basic_string<ModInt32<P>>& y) {
        using i32 = std::int32_t;
        using value_type = ModInt32<P>;
        std::basic_string<value_type> res(std::max(x.size(), y.size()), {});
        for (i32 i = 0, e = std::min(x.size(), y.size()); i != e; ++i)
            res[i] = x[i] - y[i];
        if (x.size() < y.size())
            for (i32 i = x.size(), e = y.size(); i != e; ++i) res[i] = -y[i];
        else
            std::copy(x.begin() + y.size(), x.end(), res.begin() + y.size());
        return norm(res);
    }
    template <std::uint32_t P>
    std::basic_string<ModInt32<P>> mul(std::basic_string<ModInt32<P>> x,
                                       std::basic_string<ModInt32<P>> y) {
        using i32 = std::int32_t;
        using value_type = ModInt32<P>;
        static value_type a[1 << 21], b[1 << 21];
        norm(x), norm(y);
        if (deg(x) == -1 || deg(y) == -1) return {0};
        std::basic_string<value_type> res(x.size() + y.size() - 1, {});
        if (std::min(x.size(), y.size()) <= 32) {
            i32 n = x.size(), m = y.size();
            std::fill(res.begin(), res.end(), 0);
            for (i32 i = 0; i != n; ++i)
                for (i32 j = 0; j != m; ++j) res[i + j] += x[i] * y[j];
        } else {
            std::copy(x.begin(), x.end(), a);
            std::copy(y.begin(), y.end(), b);
            i32 old_size = res.size(), len = (i32)get_len(old_size);
            std::fill(a + x.size(), a + len, 0);
            std::fill(b + y.size(), b + len, 0);
            dft(len, a), dft(len, b);
            res.resize(len);
            for (i32 i = 0; i != len; ++i) res[i] = a[i] * b[i];
            idft(len, res.data());
            res.resize(old_size);
        }
        return res;
    }
}  // namespace algebra

constexpr int mod = 998'244'353;
using mint = algebra::ModInt32<mod>;
using poly = std::basic_string<mint>;

#include <chrono>
using namespace std::chrono;
struct timer {
    high_resolution_clock::time_point begin;

    timer() {}
    timer(bool b) {
        if (b) start();
    }

    void start() {
        begin = high_resolution_clock::now();
    }

    void print() {
        cout << "Time taken: " << duration_cast<duration<double>>(high_resolution_clock::now() - begin).count() << " seconds" << endl;
    }

    double report() {
        return duration_cast<duration<double>>(high_resolution_clock::now() - begin).count();
    }
};
// Start of main put tin, end of main put tpr (tgt gives you value not printed)
#define tin timer __timer__(1);
#define tpr __timer__.print();
#define tgt __timer__.report()

ll q, Q, T, k, l, r, x, y, z;
ll n, m;

void solve();

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// Problem URL:
int main() {
    io;
    long long test_cases = 1;
//    cin >> test_cases;

    for (int i = 0; i < test_cases; i++) {
        solve();
    }
}

vector<vector<ll>> child;
ll ret;

poly rec(int l, int r, vector<poly>& v) {
    if (l == r) return v[l];

    int mid = (l + r)/2;

    poly a = rec(l, mid, v);
    poly b = rec(mid + 1, r, v);

    poly c = algebra::mul(a, b);

    for (auto& x : c) {
        if (x.v > 1) {
            x.v = 1;
        }
    }

    return c;
}

ll dfs(int v) {
    vector<ll> ve;
    ll size = 1;

    for (ll x : child[v]) {
        ve.pb(dfs(x));
        size += ve.back();
    }
    sort(ve.begin(), ve.end());
    if (ve.size() <= 1) return size;

    ll mx = ve.back();
    ve.pop_back();

    ll ans = 0;
    vector<poly> vv(ve.size());
    f0r(i, ve.size()) {
        vv[i].resize(ve[i] + 1);
        vv[i][0] = 1;
        vv[i][ve[i]] = 1;
    }

    poly r = rec(0, ve.size() - 1, vv);
    for (ll i = 0; i < r.size(); i++) {
        if (r[i].v > 0) {
            ans = max(ans, i * (size - 1 - i));
            ans = max(ans, (i + mx) * (size - 1 - (i + mx)));
        }
    }

    ret += ans;
    return size;
}

void solve() {
    cin >> n;
    child = vector<vector<ll>>(n);
    ret = 0;

    f0r(i, n - 1) {
        cin >> x;
        x--;
        child[x].pb(i + 1);
    }

    dfs(0);

    cout << ret << endl;
}
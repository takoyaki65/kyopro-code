#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;

template <class T>
inline int sz(T& x) {
    return x.size();
}

template <class T>
inline bool setmax(T& a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template <class T>
inline bool setmin(T& a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

template <int MOD>
struct Fp {
    long long val;
    constexpr Fp(long long v = 0) noexcept : val(v % MOD) {
        if (val < 0) val += MOD;
    }
    constexpr int getmod() { return MOD; }
    constexpr Fp operator-() const noexcept {
        return val ? MOD - val : 0;
    }
    constexpr Fp operator+(const Fp& r) const noexcept { return Fp(*this) += r; }
    constexpr Fp operator-(const Fp& r) const noexcept { return Fp(*this) -= r; }
    constexpr Fp operator*(const Fp& r) const noexcept { return Fp(*this) *= r; }
    constexpr Fp operator/(const Fp& r) const noexcept { return Fp(*this) /= r; }
    constexpr Fp& operator+=(const Fp& r) noexcept {
        val += r.val;
        if (val >= MOD) val -= MOD;
        return *this;
    }
    constexpr Fp& operator-=(const Fp& r) noexcept {
        val -= r.val;
        if (val < 0) val += MOD;
        return *this;
    }
    constexpr Fp& operator*=(const Fp& r) noexcept {
        val = val * r.val % MOD;
        return *this;
    }
    constexpr Fp& operator/=(const Fp& r) noexcept {
        // a * u + b * v  = 1 となるuを求める
        long long a = r.val, b = MOD, u = 1, v = 0;
        while (b) {
            long long t = a / b;
            a -= t * b;
            swap(a, b);
            u -= t * v;
            swap(u, v);
        }
        val = val * u % MOD;
        if (val < 0) val += MOD;
        return *this;
    }
    constexpr bool operator==(const Fp& r) const noexcept {
        return this->val == r.val;
    }
    constexpr bool operator!=(const Fp& r) const noexcept {
        return this->val != r.val;
    }
    friend constexpr ostream& operator<<(ostream& os, const Fp<MOD>& x) noexcept {
        return os << x.val;
    }
    friend constexpr Fp<MOD> modpow(const Fp<MOD>& a, long long n) noexcept {
        if (n == 0) return 1;
        auto t = modpow(a, n / 2);
        t = t * t;
        if (n & 1) t = t * a;
        return t;
    }
};

template <class T>
struct BiCoef {
    vector<T> fact_, inv_, finv_;
    vector<vector<T>> cmb_;
    constexpr BiCoef() {}
    constexpr BiCoef(int n) noexcept : fact_(n, 1), inv_(n, 1), finv_(n, 1), cmb_(n, vector<T>(n, 0)) {
        init(n);
    }
    constexpr void init(int n) noexcept {
        fact_.assign(n, 1), inv_.assign(n, 1), finv_.assign(n, 1);
        int MOD = fact_[0].getmod();
        for (int i = 2; i < n; ++i) {
            fact_[i] = fact_[i - 1] * i;
            inv_[i] = -inv_[MOD % i] * (MOD / i);
            finv_[i] = finv_[i - 1] * inv_[i];
        }
        cmb_[0][0] = 1;
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j <= i; ++j) {
                cmb_[i + 1][j] += cmb_[i][j];
                cmb_[i + 1][j + 1] += cmb_[i][j];
            }
        }
    }
    constexpr T com(int n, int k) const noexcept {
        if (n < k || n < 0 || k < 0) return 0;
        return cmb_[n][k];
    }
    constexpr T fact(int n) const noexcept {
        if (n < 0) return 0;
        return fact_[n];
    }
    constexpr T inv(int n) const noexcept {
        if (n < 0) return 0;
        return inv_[n];
    }
    constexpr T finv(int n) const noexcept {
        if (n < 0) return 0;
        return finv_[n];
    }
};

const int MOD = 1000000007;
using mint = Fp<MOD>;

int main() {
    int N{0}, M{0}, L{0};
    cin >> N >> M >> L;
    BiCoef<mint> cmb(N + 10);
    auto f = [&](int x) -> mint {
        if (x <= 0) return 0;
        vector<mint> path(x + 1);
        path[1] = 1;
        path[2] = 1;
        for (int i = 3; i <= x; ++i) path[i] = path[i - 1] * i;
        vector<mint> cycle(x + 1);
        for (int i = 2; i <= x; ++i) cycle[i] = path[i - 1];

        auto dp = vectors(mint(0), N + 1, M + 1);
        dp[0][0] = 1;
        repeat(i, N + 1) {
            repeat(j, M + 1) {
                // 孤立点を追加
                if (x >= 1 and i - 1 >= 0) {
                    dp[i][j] += dp[i - 1][j];
                }
                // パス
                for (int k = 2; k <= x; ++k) {
                    int vcnt = i - k;
                    int ecnt = j - (k - 1);
                    if (vcnt < 0 or ecnt < 0) break;
                    dp[i][j] += dp[vcnt][ecnt] * cmb.com(N - vcnt - 1, k - 1) * path[k];
                }
                // サイクル
                for (int k = 2; k <= x; ++k) {
                    int vcnt = i - k;
                    int ecnt = j - k;
                    if (vcnt < 0 or ecnt < 0) break;
                    dp[i][j] += dp[vcnt][ecnt] * cmb.com(N - vcnt - 1, k - 1) * cycle[k];
                }
            }
        }
        return dp[N][M];
    };
    /* 
    cout << "f(L): " << f(L) << endl;
    cout << "f(L-1): " << f(L - 1) << endl;
    */
    cout << f(L) - f(L - 1) << endl;
    return 0;
}
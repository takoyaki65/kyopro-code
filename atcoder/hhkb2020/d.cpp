#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
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
    constexpr BiCoef() {}
    constexpr BiCoef(int n) noexcept : fact_(n, 1), inv_(n, 1), finv_(n, 1) {
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
    }
    constexpr T com(int n, int k) const noexcept {
        if (n < k || n < 0 || k < 0) return 0;
        return fact_[n] * finv_[k] * finv_[n - k];
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
    int T;
    cin >> T;
    while (T--) {
        int N, A, B;
        cin >> N >> A >> B;
        mint res = mint(N - A + 1) * mint(N - A + 1) * mint(N - B + 1) * mint(N - B + 1);

        //cout << "res: " << res << endl;
        if (A > B) swap(A, B);
        mint P = min(N - B, A - 1);
        //cout << "P: " << P << endl;
        if (0 < P.val) {
            mint sub1 = P * mint(N - B + 1) - P * (P + 1) / 2;
            sub1 = sub1 * sub1 * 4;
            //cout << "sub1: " << sub1 << endl;
            mint sub2 = mint(B - A + 1) * mint(N - B + 1) *
                        (P * mint(N - B + 1) - P * (P + 1) / 2);
            sub2 *= 4;
            //cout << "sub2: " << sub2 << endl;
            res -= (sub1 + sub2);
        }
        mint sub3 = mint(B - A + 1) * mint(B - A + 1) * mint(N - B + 1) * mint(N - B + 1);
        res -= sub3;
        //cout << "sub3: " << sub3 << endl;
        cout << res << endl;
    }
    return 0;
}
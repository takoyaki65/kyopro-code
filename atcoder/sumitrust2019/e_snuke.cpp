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

const int MOD = 1000000007;
using mint = Fp<MOD>;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    repeat(i, n) cin >> a[i];
    vector<int> c(n + 1);
    c[0] = 3;
    mint ans = 1;
    repeat(i, n) {
        if (!c[a[i]]) {
            cout << 0 << endl;
            return 0;
        }
        ans *= c[a[i]];
        c[a[i]]--;
        c[a[i] + 1]++;
    }
    cout << ans << endl;
    return 0;
}
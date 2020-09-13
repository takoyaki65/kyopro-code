#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;
template <class T>
void setmax(T& a, T const& b) {
    if (a < b) a = b;
}

template <class T>
void setmin(T& a, T const& b) {
    if (a > b) a = b;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

//const int mod = 1000000007;
const int mod = 998244353;
template <typename T, T MOD = 1000000007>
struct Mint {
    static constexpr T mod = MOD;
    T v;
    Mint() : v(0) {}
    Mint(signed v) : v(v) {}
    Mint(long long t) {
        v = t % MOD;
        if (v < 0) v += MOD;
    }

    Mint pow(long long k) {
        Mint res(1), tmp(v);
        while (k) {
            if (k & 1) res *= tmp;
            tmp *= tmp;
            k >>= 1;
        }
        return res;
    }

    static Mint add_identity() { return Mint(0); }
    static Mint mul_identity() { return Mint(1); }

    Mint inv() { return pow(MOD - 2); }

    Mint& operator+=(Mint a) {
        v += a.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    Mint& operator-=(Mint a) {
        v += MOD - a.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    Mint& operator*=(Mint a) {
        v = 1LL * v * a.v % MOD;
        return *this;
    }
    Mint& operator/=(Mint a) { return (*this) *= a.inv(); }

    Mint operator+(Mint a) const { return Mint(v) += a; }
    Mint operator-(Mint a) const { return Mint(v) -= a; }
    Mint operator*(Mint a) const { return Mint(v) *= a; }
    Mint operator/(Mint a) const { return Mint(v) /= a; }

    Mint operator-() const { return v ? Mint(MOD - v) : Mint(v); }

    bool operator==(const Mint a) const { return v == a.v; }
    bool operator!=(const Mint a) const { return v != a.v; }
    bool operator<(const Mint a) const { return v < a.v; }

    static Mint comb(long long n, int k) {
        Mint num(1), dom(1);
        for (int i = 0; i < k; i++) {
            num *= Mint(n - i);
            dom *= Mint(i + 1);
        }
        return num / dom;
    }
};
template <typename T, T MOD>
constexpr T Mint<T, MOD>::mod;
template <typename T, T MOD>
ostream& operator<<(ostream& os, Mint<T, MOD> m) {
    os << m.v;
    return os;
}
template <typename T, T MOD>
istream& operator>>(istream& os, Mint<T, MOD>& m) {
    os >> m.v;
    return os;
}

// https://github.com/atcoder-live/library/blob/master/comb.cpp
template <typename T, T MOD = 1000000007>
struct combination {
    vector<Mint<T, MOD>> fact, ifact;
    combination(int n) : fact(n + 1), ifact(n + 1) {
        assert(n < mod);
        fact[0] = 1;
        for (int i = 1; i <= n; ++i) {
            fact[i] = fact[i - 1] * i;
        }
        ifact[n] = fact[n].inv();
        for (int i = n; i >= 1; --i) {
            ifact[i - 1] = ifact[i] * i;
        }
    }
    Mint<T, MOD> operator()(int n, int k) {
        if (k < 0 || k > n) return Mint<T, MOD>(0);
        return fact[n] * ifact[k] * ifact[n - k];
    }
};

using Int = Mint<long long>;

int main() {
    int N;
    cin >> N;
    if (N == 1) {
        cout << 0 << endl;
        return 0;
    }

    Int res(1);
    res = Int(10LL).pow(N);

    // 「0が使われていない」 + 「9が使われていない」 - 「0と9両方使われていない」
    Int sub = Int(9LL).pow(N) * 2LL - Int(8LL).pow(N);
    res -= sub;
    cout << res << endl;
    return 0;
}
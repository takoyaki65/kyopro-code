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

using mint = Mint<long long>;
const int MAX_AK = 11000;

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    repeat(i, N) cin >> A[i];
    auto dp = vectors(mint(), N + 1, MAX_AK);
    dp[0][0] = 1;
    for (int ai : A) {
        for (int i = N - 1; i >= 0; --i) {
            repeat(j, MAX_AK) {
                if (j - ai >= 0) {
                    dp[i + 1][j] += dp[i][j - ai];
                }
            }
        }
    }
    mint res = 0;
    repeat_from(i, 1, N + 1) {
        repeat_from(j, i * K, MAX_AK) {
            res += dp[i][j];
        }
    }
    cout << res << endl;
    return 0;
}
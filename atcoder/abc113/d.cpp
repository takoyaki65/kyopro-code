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

using Int = Mint<long long>;

int main() {
    int H, W, K;
    cin >> H >> W >> K;

    vector<Int> f(W + 1);  // f[i] := i本連続に並んだ縦棒の間に横棒を置く通り
    assert(W >= 1);
    f[0] = f[1] = 1;
    repeat_from(i, 2, W + 1) {
        f[i] = f[i - 1] + f[i - 2];
    }

    vector<Int> dp1(W), dp2(W);
    dp1[0] = 1;
    repeat(i, H) {
        repeat(j, W) dp2[j] = 0LL;
        repeat(j, W) {
            dp2[j] += dp1[j] * f[j] * f[W - 1 - j];
            if (j - 1 >= 0) {
                //assert(j - 1 >= 0);
                //assert(W - j - 1 >= 0 && W - j - 1 < W);
                dp2[j] += dp1[j - 1] * f[j - 1] * f[W - j - 1];
            }
            if (j + 1 < W) {
                //assert(j + 1 < W);
                //assert(W - j - 2 >= 0 && W - j - 2 < W);
                dp2[j] += dp1[j + 1] * f[j] * f[W - j - 2];
            }
        }
        dp1.swap(dp2);
    }
    /* 
    cout << "res: " << endl;
    repeat(i, W) cout << dp1[i] << " ";
    cout << endl;
    */
    cout << dp1[K - 1] << endl;

    return 0;
}
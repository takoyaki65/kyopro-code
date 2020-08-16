#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int, int>;

// auto mod int
// https://youtu.be/L8grWxBlIZ4?t=9858
// https://youtu.be/ERZuLAxZffQ?t=4807 : optimize
// https://youtu.be/8uowVvQ_-Mo?t=1329 : division
const int mod = 1000000007;
struct mint {
    ll x;  // typedef long long ll;
    mint(ll x = 0) : x((x % mod + mod) % mod) {}
    mint operator-() const { return mint(-x); }
    mint& operator+=(const mint a) {
        if ((x += a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += mod - a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator*=(const mint a) {
        (x *= a.x) %= mod;
        return *this;
    }
    mint operator+(const mint a) const { return mint(*this) += a; }
    mint operator-(const mint a) const { return mint(*this) -= a; }
    mint operator*(const mint a) const { return mint(*this) *= a; }
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t >> 1);
        a *= a;
        if (t & 1) a *= *this;
        return a;
    }

    // for prime mod
    mint inv() const { return pow(mod - 2); }
    mint& operator/=(const mint a) { return *this *= a.inv(); }
    mint operator/(const mint a) const { return mint(*this) /= a; }
};
istream& operator>>(istream& is, mint& a) { return is >> a.x; }
ostream& operator<<(ostream& os, const mint& a) { return os << a.x; }

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<int> s, t;
    rep(i, n) {
        cin >> a[i];
        if (a[i] < 0)
            t.push_back(a[i]);
        else
            s.push_back(a[i]);
    }

    int S = s.size();
    int T = t.size();
    bool ok = false;
    if (S > 0) {
        if (n == k)
            ok = (T % 2 == 0);
        else
            ok = true;
    } else {
        ok = (k % 2 == 0);
    }

    mint ans = 1;
    if (!ok) {
        sort(a.begin(), a.end(), [](int x, int y) {
            return abs(x) < abs(y);
        });
        rep(i, k) ans *= a[i];
    } else {
        sort(s.begin(), s.end());
        sort(t.rbegin(), t.rend());
        if (k % 2 == 1) {
            ans *= s.back();
            s.pop_back();
        }
        vector<ll> p;
        while (s.size() >= 2) {
            ll x = s.back();
            s.pop_back();
            x *= s.back();
            s.pop_back();
            p.push_back(x);
        }
        while (t.size() >= 2) {
            ll x = t.back();
            t.pop_back();
            x *= t.back();
            t.pop_back();
            p.push_back(x);
        }
        sort(p.rbegin(), p.rend());
        rep(i, k / 2) ans *= p[i];
    }

    cout << ans << endl;
    return 0;
}

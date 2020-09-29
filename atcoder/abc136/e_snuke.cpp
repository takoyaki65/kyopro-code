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
#define sz(x) int(x.size())
using namespace std;
template <class T>
void setmax(T &a, T const &b) {
    if (a < b) a = b;
}

template <class T>
void setmin(T &a, T const &b) {
    if (a > b) a = b;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

// 操作しても総和は変わらない
// gcd(A1 , A2 , ... , AN) = gとすると、(A1 + A2 + ... + AN)%g == 0
// なので、Ai + diと修正するとき
// あり得る答えの候補はsum(Ai)の約数{gi}
// sum(di) == 0
// (diの内の正の数の和) = -(diの内の負の数の和)
// を満たし、(Ai + di)がすべてgiの倍数となるようにすることができるか調べる

vector<long long> divisor(long long n) {
    vector<long long> ret;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            ret.push_back(i);
            if (i * i != n) ret.push_back(n / i);
        }
    }
    sort(ret.begin(), ret.end());
    return (ret);
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    repeat(i, n) cin >> a[i];

    long long sum = 0;
    for (int x : a) sum += x;
    vector<long long> sdiv = divisor(sum);

    long long ans = 1;
    for (long long x : sdiv) {
        long long need = 1e9 + 100;
        {
            vector<long long> r(n);
            repeat(i, n) r[i] = a[i] % x;
            sort(r.begin(), r.end());
            long long tot = 0;
            repeat(i, n) tot += r[i];
            int right = tot / x;
            int left = n - right;
            need = 0;
            repeat(i, left) need += r[i];
        }
        if (need <= k) setmax(ans, x);
    }
    cout << ans << endl;

    return 0;
}
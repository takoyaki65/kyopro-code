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

// 尺取り(sliding window)
// 0が含まれるなら、答えはN、そうでないなら尺取りしよう

int main() {
    int N;
    long long K;
    cin >> N >> K;
    vector<long long> s(N);
    repeat(i, N) cin >> s[i];
    for (int x : s) {
        if (x == 0) {
            cout << N << endl;
            return 0;
        }
    }

    int res = 0;
    int l = 0, r = 0;
    long long mul = 1;
    while (l < N && l <= r) {
        while (r < N && mul * s[r] <= K) mul *= s[r++];
        setmax(res, r - l);

        mul /= s[l];
        ++l;
    }
    cout << res << endl;
    return 0;
}
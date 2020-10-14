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
inline int sz(T &x) {
    return x.size();
}

template <class T>
inline bool setmax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template <class T>
inline bool setmin(T &a, T b) {
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

// (a_i) * (a_i が最小値に選ばれる区間の個数)

int main() {
    int N;
    cin >> N;
    vector<int> a(N);
    repeat(i, N) cin >> a[i];
    repeat(i, N)-- a[i];
    vector<int> pos(N);
    repeat(i, N) pos[a[i]] = i;
    set<int> s;
    repeat(i, N) s.insert(pos[i]);
    s.insert(-1);
    s.insert(N);

    long long res = 0;
    for (int i = N - 1; i >= 0; --i) {
        auto itr = s.find(pos[i]);
        int l = *prev(itr), r = *next(itr);
        res += (long long)(i + 1) * (pos[i] - l) * (r - pos[i]);
        s.erase(itr);
    }
    cout << res << endl;

    return 0;
}
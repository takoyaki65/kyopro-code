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

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> p(n);
    repeat(i, n) cin >> p[i];

    // t[i] := [i, i + k)の区間が昇順に並んでいるか
    //          昇順に並んでいないな0より大きい値
    //          昇順に並んでいたら0
    vector<int> t(n - k + 1);
    {
        int cnt = 0, j = 1;
        repeat(i, n - k + 1) {
            while (j < i + k) {
                if (p[j - 1] > p[j]) ++cnt;
                ++j;
            }
            t[i] = cnt;
            if (p[i] > p[i + 1]) --cnt;
        }
    }
    // sm[i] := [i-1, i+k-1)をソートした結果と [i, i+k)をソートした結果が
    //          同じになるなら1
    //          同じにならないなら0
    vector<int> sm(n - k + 1);
    {
        set<int> s;
        int j = 0;
        repeat(i, n - k) {
            while (j < i + k + 1)
                s.insert(p[j++]);
            if (*s.begin() == p[i] && *prev(s.end()) == p[j - 1])
                sm[i + 1] = 1;
            s.erase(p[i]);
        }
    }
    int ans = 0, z = 0;
    // ansには、[i, i+k)をソートした結果が同じになるiの区間の個数(各区間の切れ目)を入れる
    // zには、ソートしても変わらないiの個数を入れる
    repeat(i, n - k + 1) {
        if (!sm[i]) {
            if (t[i])
                ans++;
            else
                z++;
        }
    }
    ans += bool(z);
    cout << ans << endl;
    return 0;
}
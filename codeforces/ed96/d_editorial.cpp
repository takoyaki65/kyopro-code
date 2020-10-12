//https://codeforces.com/blog/entry/83614
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

char buf[200043];

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cin >> buf;
        string s = buf;
        assert(sz(s) == n);
        queue<int> que;
        int cur = 0;
        repeat(i, n) {
            if (i > 0 and s[i] != s[i - 1])
                ++cur;

            if (i > 0 and s[i] == s[i - 1])
                que.push(cur);
        }
        int deleted = 0;
        int score = 0;
        repeat(i, n) {
            if (que.empty()) break;

            que.pop();
            deleted++;
            score++;
            while (!que.empty() and que.front() == i) {
                que.pop();
                deleted++;
            }
            deleted++;
            // cerr << deleted << endl;
        }
        score += (n - deleted + 1) / 2;
        cout << score << endl;
    }
}
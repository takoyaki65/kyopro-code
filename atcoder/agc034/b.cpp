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

// 左にある'BC'から操作していく

int main() {
    string S;
    cin >> S;
    int N = sz(S);
    string T;
    {
        int cur = 0;
        while (cur < N) {
            if (S[cur] == 'A') {
                T += 'A';
                ++cur;
            } else if (cur + 1 < N and S[cur] == 'B' and S[cur + 1] == 'C') {
                T += 'D';
                cur += 2;
            } else {
                T += S[cur];
                ++cur;
            }
        }
    }

    int M = sz(T);
    long long res = 0;
    int a = 0;
    repeat(i, M) {
        if (T[i] == 'A') {
            ++a;
        } else if (T[i] == 'D') {
            res += a;
        } else {
            a = 0;
        }
    }
    cout << res << endl;
    return 0;
}
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

// 実は、連続に並んだ二匹が狼/羊かを決めると、他は一意に決まるのでは？
// それで、矛盾なくできるか検証しよう

int main() {
    int N;
    string S;
    cin >> N >> S;

    vector<int> res(N);
    bool flg = false;
    for (int bit = 0; bit < (1 << 2); ++bit) {
        res[0] = (bit & 1) ? 1 : 0;
        res[1] = ((bit >> 1) & 1) ? 1 : 0;
        repeat_from(j, 2, N) {
            if (res[j - 1]) {
                if (S[j - 1] == 'o') {
                    res[j] = res[j - 2];
                } else {
                    res[j] = !res[j - 2];
                }
            } else {
                if (S[j - 1] == 'o') {
                    res[j] = !res[j - 2];
                } else {
                    res[j] = res[j - 2];
                }
            }
        }
        // N-1 と 0で矛盾がないか検証
        if (res[N - 1]) {
            if (S[N - 1] == 'o' && res[0] != res[N - 2]) continue;
            if (S[N - 1] == 'x' && res[0] == res[N - 2]) continue;
        } else {
            if (S[N - 1] == 'x' && res[0] != res[N - 2]) continue;
            if (S[N - 1] == 'o' && res[0] == res[N - 2]) continue;
        }
        if (res[0]) {
            if (S[0] == 'o' && res[1] != res[N - 1]) continue;
            if (S[0] == 'x' && res[1] == res[N - 1]) continue;
        } else {
            if (S[0] == 'x' && res[1] != res[N - 1]) continue;
            if (S[0] == 'o' && res[1] == res[N - 1]) continue;
        }
        flg = true;
        break;
    }

    if (flg) {
        for (int i = 0; i < N; ++i) {
            cout << (res[i] ? 'S' : 'W');
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }
    return 0;
}
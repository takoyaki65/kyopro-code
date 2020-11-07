#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
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

// 下3桁が8の倍数になればOk
// Sは0を含まないので特殊なケースは無いものと考えてOk

int main() {
    string S;
    cin >> S;
    vector<int> Num(10, 0);
    for (char ch : S) {
        ++Num[ch - '0'];
    }

    if (S.size() <= 3) {
        sort(begin(S), end(S));
        for (int X = 8; X < 1000; X += 8) {
            string u = to_string(X);
            sort(begin(u), end(u));
            if (S == u) {
                cout << "Yes" << endl;
                return 0;
            }
        }
        cout << "No" << endl;
        return 0;
    }

    for (int X = 8; X < 1000; X += 8) {
        string u3 = to_string(X);
        if (sz(u3) < 3) continue;
        vector<int> u3_Num(10, 0);
        for (char ch : u3) {
            ++u3_Num[ch - '0'];
        }
        if (u3_Num[0] > 0) continue;
        bool flg = true;
        repeat(i, 10) {
            if (u3_Num[i] > Num[i]) {
                flg = false;
                break;
            }
        }
        if (flg) {
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
    return 0;

    return 0;
}
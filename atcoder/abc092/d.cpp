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

int main() {
    int A, B;
    cin >> A >> B;
    vector<string> res(100);
    repeat(i, 100) {
        res[i] = "";
        repeat(j, 100) {
            res[i] += (i < 50) ? '#' : '.';
        }
    }

    int num = 0;
    int x = 0, y = 0;
    while (num < A - 1) {
        res[x][y] = '.';
        y += 2;
        if (y >= 100) {
            x += 2;
            y = 0;
        }
        num++;
    }

    num = 0;
    x = 99, y = 0;
    while (num < B - 1) {
        res[x][y] = '#';
        y += 2;
        if (y >= 100) {
            x -= 2;
            y = 0;
        }
        num++;
    }

    cout << "100 100" << endl;
    repeat(i, 100) {
        assert(res[i].size() == 100);
        cout << res[i] << endl;
    }
    return 0;
}
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

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, -1, 0, 1};

int main() {
    int h{0}, w{0}, n{0}, m{0};
    cin >> h >> w >> n >> m;
    vector<int> lx(n), ly(n), bx(m), by(m);
    repeat(i, n) {
        cin >> ly[i] >> lx[i];
        --ly[i], --lx[i];
    }
    repeat(i, m) {
        cin >> by[i] >> bx[i];
        --by[i], --bx[i];
    }

    auto tate = vectors(0, h, w);
    auto yoko = vectors(0, h, w);

    repeat(i, m) {
        tate[by[i]][bx[i]] = -1;
        yoko[by[i]][bx[i]] = -1;
    }

    repeat(i, n) {
        if (tate[ly[i]][lx[i]] == 1) continue;
        tate[ly[i]][lx[i]] = 1;
        repeat(k, 2) {
            int x_cur = lx[i];
            int y_cur = ly[i];
            int dir = k ? 1 : -1;
            while (true) {
                y_cur += dir;
                if (x_cur < 0 or x_cur >= w or y_cur < 0 or y_cur >= h) break;
                if (tate[y_cur][x_cur] == -1) break;
                tate[y_cur][x_cur] = 1;
            }
        }
    }

    repeat(i, n) {
        if (yoko[ly[i]][lx[i]] == 1) continue;
        yoko[ly[i]][lx[i]] = 1;
        repeat(k, 2) {
            int x_cur = lx[i];
            int y_cur = ly[i];
            int dir = k ? 1 : -1;
            while (true) {
                x_cur += dir;
                if (x_cur < 0 or x_cur >= w or y_cur < 0 or y_cur >= h) break;
                if (yoko[y_cur][x_cur] == -1) break;
                yoko[y_cur][x_cur] = 1;
            }
        }
    }

    int res = 0;
    repeat(y, h) {
        repeat(x, w) {
            if (tate[y][x] == 1 or yoko[y][x] == 1) ++res;
        }
    }
    cout << res << endl;
    return 0;
}
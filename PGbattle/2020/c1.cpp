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

int main() {
    int H{0}, W{0};
    cin >> H >> W;
    int sx{0}, sy{0}, gx{0}, gy{0};
    cin >> sx >> sy >> gx >> gy;
    --sx, --sy, --gx, --gy;
    vector<string> grid(H);
    repeat(i, H) cin >> grid[i];

    int x = sx, y = sy;
    int cnt = 0;
    int dir = 1;
    // (位置, 向き)の状態数は 4*H*W通り
    // 前回たどった状態(位置、向き)と同じ状態に戻ったら無限ループしていることになるので、そこで打ち切り
    // 鳩ノ巣原理
    long long max_cnt = 4LL * H * W + 100;
    const int dx[] = {0, -1, 0, 1};
    const int dy[] = {-1, 0, 1, 0};
    while (true) {
        // 左向く
        dir = (dir - 1 + 4) % 4;
        int nx = 0, ny = 0, nxt = 0;
        for (nxt = 0; nxt < 4; ++nxt) {
            nx = x + dx[(dir + nxt) % 4];
            ny = y + dy[(dir + nxt) % 4];
            if (nx < 0 or nx >= H or ny < 0 or ny >= W) continue;
            if (grid[nx][ny] == '#') continue;
            break;
        }
        if (nxt == 4) {
            cout << -1 << endl;
            return 0;
        }
        x = nx;
        y = ny;
        //cout << "x: " << x << " y: " << y << endl;
        dir = (dir + nxt) % 4;
        ++cnt;
        if (x == gx and y == gy) {
            cout << cnt << endl;
            return 0;
        }
        --max_cnt;
        if (max_cnt < 0) {
            cout << -1 << endl;
            return 0;
        }
    }
}
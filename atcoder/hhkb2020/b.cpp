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

const int dx[] = {0, 1};
const int dy[] = {1, 0};

int main() {
    int H, W;
    cin >> H >> W;
    vector<string> S(H);
    repeat(i, H) cin >> S[i];
    int cnt = 0;
    repeat(i, H) {
        repeat(j, W) {
            repeat(k, 2) {
                int ny = i + dy[k];
                int nx = j + dx[k];
                if (ny < 0 || ny >= H || nx < 0 || nx >= W) continue;
                if (S[i][j] == '.' and S[ny][nx] == '.') {
                    ++cnt;
                }
            }
        }
    }
    cout << cnt << endl;
    return 0;
}
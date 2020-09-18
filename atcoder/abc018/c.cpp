#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
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

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int main() {
    int R, C, K;
    cin >> R >> C >> K;
    vector<string> s(R);
    repeat(i, R) cin >> s[i];

    auto d = vectors(-1, R, C);
    queue<pair<int, int>> que;
    repeat(i, R) {
        repeat(j, C) {
            if (s[i][j] == 'x') {
                d[i][j] = 0;
                que.emplace(i, j);
            }
        }
    }
    while (!que.empty()) {
        int x = que.front().first;
        int y = que.front().second;
        que.pop();
        repeat(i, 4) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
            if (d[nx][ny] == -1) {
                d[nx][ny] = d[x][y] + 1;
                que.emplace(nx, ny);
            }
        }
    }

    int res = 0;
    repeat_from(x, K - 1, R - K + 1) {
        repeat_from(y, K - 1, C - K + 1) {
            if (d[x][y] >= K) {
                ++res;
            }
        }
    }
    cout << res << endl;
    return 0;
}